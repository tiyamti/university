import copy
import random
from abc import abstractmethod
import numpy as np
import matplotlib
from sklearn.feature_selection import mutual_info_classif
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

# matplotlib.use('TkAgg')
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from google.colab import files
uploaded = files.upload()


###########################################################################################
class FuzzySet:
    def __init__(self, is_continuous, alpha):
        self.is_continuous = is_continuous
        self.alpha = alpha

    def cut(self, x):
        membership_value = self.membership_func(x)
        if membership_value > self.alpha:
            return self.alpha
        return membership_value

    @abstractmethod
    def membership_func(self, x):
        """Abstract method for area calculation"""
        pass


class TriangleSet(FuzzySet):
    def __init__(self, is_continuous, a, b, c):
        super().__init__(is_continuous, 1)
        self.a = a
        self.b = b
        self.c = c

    def membership_func(self, x):
        if not self.is_continuous:
            x = int(x)
        if self.a == self.b:
            return np.maximum(np.minimum(1, (self.c - x) / (self.c - self.b)), 0)
        elif self.c == self.b:
            return np.maximum(np.minimum(1, (x - self.a) / (self.b - self.a)), 0)
        return np.maximum(np.minimum((x - self.a) / (self.b - self.a), (self.c - x) / (self.c - self.b)), 0)


class CategoricalSet(FuzzySet):
    def __init__(self, category_num):
        super().__init__(False, 1)
        self.category_num = category_num

    def membership_func(self, x):
        if self.category_num == x:
            return 1
        else:
            return 0


class LinguisticVariable:
    def __init__(self, name, lower_limit, upper_limit):
        self.name = name
        self.lower_limit = lower_limit
        self.upper_limit = upper_limit
        self.fuzzy_sets = {}

    def plot_variable(self):
        plt.figure(figsize=(8, 4))
        x = np.linspace(self.lower_limit, self.upper_limit, 500)

        for name, fs in self.fuzzy_sets.items():
            y = [fs.membership_func(val) for val in x]
            plt.plot(x, y, label=name)

        plt.title(f"Membership Functions: {self.name}")
        plt.xlabel("Value")
        plt.ylabel("Membership Degree")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.ylim(0, 1.05)
        plt.tight_layout()
        plt.show()


class Rule:
    def __init__(self, antecedents, result, weight):
        self.antecedents = antecedents
        self.result = result
        self.weight = weight

    def __eq__(self, other):
        if not isinstance(other, Rule):
            return False
        return (self.antecedents == other.antecedents) and (self.result == other.result)

    def __hash__(self):
        return hash((self.antecedents, self.result))


class FIS:
    def __init__(self, train_set, linguistic_variables_list):
        self.train_set = train_set
        self.rules = []
        self.linguistic_variables = linguistic_variables_list

    def find_matching_rule(self, target_rule):
        for rule in self.rules:
            if rule == target_rule:
                return rule
        return None

    def wang_mendel(self, max_rules=50):
        count = 0
        for _, row in self.train_set.iterrows():
            if count > max_rules:
                break
            antecedents = []
            cf = 1
            row_enum = enumerate(row)
            for i, x in row_enum:
                membership_degrees = [fs.membership_func(x) for fs in self.linguistic_variables[i].fuzzy_sets.values()]
                set_names = list(self.linguistic_variables[i].fuzzy_sets.keys())
                max_membership_degree = max(membership_degrees)
                best_set = set_names[np.argmax(membership_degrees)]
                if i < len(row) - 1:
                    cf *= max_membership_degree
                    antecedents.append(best_set)
                else:
                    rule = Rule(copy.deepcopy(antecedents), best_set, cf)
                    same_rule = self.find_matching_rule(rule)
                    if same_rule is None:
                        self.rules.append(rule)
                    else:
                        if same_rule.weight < rule.weight:
                            same_rule.weight = rule.weight
            count += 1

    def mamdani(self, inputs):
        weight_prod_z = 0
        sum_weight = 0
        for rule in self.rules:
            antecedents_memberships = []
            i = 0
            for antecedent in rule.antecedents:
                membership = self.linguistic_variables[i].fuzzy_sets[antecedent].membership_func(inputs.iloc[i])
                antecedents_memberships.append(membership)
                i += 1
            alpha = min(antecedents_memberships)
            output_set = self.linguistic_variables[i].fuzzy_sets[rule.result]
            if isinstance(output_set, CategoricalSet):
                weight_prod_z += output_set.category_num * alpha
                sum_weight += alpha
        if sum_weight == 0:
            return 0
        return int(weight_prod_z / sum_weight)


class Chromosome:
    def __init__(self, num_rules, chromosome_list, num_element_in_rule=11):
        self.num_rules = num_rules
        self.chromosome_list = chromosome_list
        self.num_element_in_rule = num_element_in_rule

    def modify_gen(self, rule_idx, gen_index):
        rule = self.chromosome_list[rule_idx]
        target_index = next(i for i, var in enumerate(fis.linguistic_variables) if var.name == "Target")

        if gen_index == self.num_element_in_rule - 1:
            fuzzy_set_names = list(fis.linguistic_variables[target_index].fuzzy_sets.keys())
            rule.result = random.choice(fuzzy_set_names)
        else:
            fuzzy_set_names = list(fis.linguistic_variables[gen_index].fuzzy_sets.keys())
            rule.antecedents[gen_index] = random.choice(fuzzy_set_names)


class Genetic:
    def __init__(self, fis_model, train_set, population_size=20, mutation_rate=0.4,
                 crossover_rate=0.9, generations=35, patience=10):
        self.fis_model = fis_model
        self.patience = patience
        self.train_set, self.valid_set = train_test_split(train_set, test_size=0.2, random_state=42,
                                                          stratify=train_set["Target"])
        self.population_size = population_size
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.generations = generations
        self.population = self.init_population()
        self.feature_selection_history = []
        self.accuracy_history = []

    def init_population(self):
        rules = copy.deepcopy(self.fis_model.rules)
        for i in range(200):
            rule = self.make_random_rule()
            if rule not in rules:
                rules.append(rule)
        chromosome_rules_size = int(len(rules) / self.population_size)
        rule_idx = 0
        population = []
        for i in range(self.population_size):
            chromosome_list = []
            for _ in range(chromosome_rules_size):
                chromosome_list.append(
                    Rule(rules[rule_idx].antecedents, rules[rule_idx].result,
                         rules[rule_idx].weight))
                rule_idx += 1
            population.append(Chromosome(chromosome_rules_size, copy.deepcopy(chromosome_list)))
        while rule_idx < len(self.fis_model.rules):
            population[self.population_size - 1].chromosome_list.append(
                Rule(rules[rule_idx].antecedents, rules[rule_idx].result,
                     rules[rule_idx].weight))
            rule_idx += 1
        return population

    def fitness(self, chromosome):
        temp_fis = FIS(self.train_set, self.fis_model.linguistic_variables)
        temp_fis.rules = copy.deepcopy(chromosome.chromosome_list)
        y_true = []
        y_pred = []
        for _, row in self.valid_set.iterrows():
            predicted = temp_fis.mamdani(row)
            y_pred.append(predicted)
            y_true.append(row['Target'])

        acc = accuracy_score(y_true, y_pred)
        f1 = f1_score(y_true, y_pred, average='weighted')
        penalty = chromosome.num_rules / len(self.fis_model.rules)
        fitness_value = 0.5 * acc + 0.3 * f1 + 0.2 * (1 - penalty)

        return fitness_value

    def crossover(self, parent1, parent2):
        rules1 = parent1.chromosome_list
        rules2 = parent2.chromosome_list

        min_len = min(len(rules1), len(rules2))
        # too short for crossover
        if min_len < 2:
            return copy.deepcopy(parent1), copy.deepcopy(parent2)

        crossover_point = random.randint(1, min_len - 1)

        child1_rules = copy.deepcopy(rules1[:crossover_point] + rules2[crossover_point:])
        child2_rules = copy.deepcopy(rules2[:crossover_point] + rules1[crossover_point:])

        child1 = Chromosome(len(child1_rules), child1_rules)
        child2 = Chromosome(len(child2_rules), child2_rules)

        return child1, child2

    def mutation(self, parent):
        if random.random() < self.mutation_rate:
            rand_op = random.random()
            if rand_op < 0.5:
                for rule_idx in range(parent.num_rules):
                    for gen_idx in range(parent.num_element_in_rule):
                        if random.random() < 0.5:
                            parent.modify_gen(rule_idx, gen_idx)
            elif 0.5 <= rand_op < 0.75 and parent.num_rules > 5:
                remove_idx = random.randint(0, parent.num_rules - 1)
                del parent.chromosome_list[remove_idx]
                parent.num_rules -= 1
            else:
                rule = self.make_random_rule()
                if rule not in parent.chromosome_list:
                    parent.chromosome_list.append(rule)
                    parent.num_rules += 1

    def make_random_rule(self):
        antecedents = []
        for i, var in enumerate(self.fis_model.linguistic_variables):
            if var.name == "Target":
                continue
            fuzzy_set_names = list(var.fuzzy_sets.keys())
            antecedents.append(random.choice(fuzzy_set_names))
        target_var = next(var for var in self.fis_model.linguistic_variables if var.name == "Target")
        result = random.choice(list(target_var.fuzzy_sets.keys()))
        weight = random.uniform(0.5, 1.0)
        return Rule(antecedents, result, weight)

    def parent_selection(self, fitness_scores, k=5):
        selected = random.sample(list(enumerate(fitness_scores)), k)
        winner = max(selected, key=lambda x: x[1])
        return self.population[winner[0]]

    def run(self):
        print("Genetic Algorithm Running...")
        fitness_scores = [self.fitness(ch) for ch in self.population]
        best_fitness = max(fitness_scores)
        for generation in range(self.generations):
            new_population = []
            for _ in range(self.population_size // 2):
                parent1 = self.parent_selection(fitness_scores)
                parent2 = self.parent_selection(fitness_scores)
                if random.random() < self.crossover_rate:
                    child1, child2 = self.crossover(parent1, parent2)
                else:
                    child1, child2 = copy.deepcopy(parent1), copy.deepcopy(parent2)
                self.mutation(child1)
                self.mutation(child2)
                new_population.append(child1)
                new_population.append(child2)
            print(max(fitness_scores))
            

            self.accuracy_history.append(best_fitness)
            self.population = new_population

            fitness_scores = [self.fitness(ch) for ch in self.population]
            best_fitness = max(fitness_scores)
            
        print("Genetic Algorithm Completed.")
        return self.population[np.argmax(fitness_scores)]

    def plot_genetic_accuracy(self):
        plt.figure(figsize=(8, 5))
        plt.plot(range(len(self.accuracy_history)), self.accuracy_history, marker='o', linestyle='-', color='b')
        plt.title("Genetic Algorithm Accuracy Over Generations")
        plt.xlabel("Generation")
        plt.ylabel("Best Fitness (Accuracy)")
        plt.grid(True, linestyle='--', alpha=0.6)
        plt.tight_layout()
        plt.show()


#############################################################################################


def plot_dataset_columns(dataset):
    numeric_cols = dataset.select_dtypes(include=['int64', 'float64']).columns
    for col in numeric_cols:
        plt.figure()
        plt.hist(dataset[col].dropna(), bins=20)
        plt.title(f'Distribution of {col}')
        plt.xlabel(col)
        plt.ylabel('Frequency')
        plt.tight_layout()
        plt.show()

    categorical_cols = dataset.select_dtypes(include=['object', 'category']).columns
    for col in categorical_cols:
        plt.figure()
        dataset[col].value_counts().plot(kind='bar')
        plt.title(f'Value Counts of {col}')
        plt.xlabel(col)
        plt.ylabel('Count')
        plt.xticks(rotation=45, ha='right')
        plt.tight_layout()
        plt.show()


def plot_correlation_matrix(dataset):
    numeric_cols = dataset.select_dtypes(include=['int64', 'float64']).columns
    plt.figure(figsize=(13, 9))
    corr = dataset[numeric_cols].corr()
    plt.imshow(corr, cmap='viridis', interpolation='none')
    plt.colorbar()
    plt.xticks(range(len(numeric_cols)), numeric_cols, rotation=90)
    plt.yticks(range(len(numeric_cols)), numeric_cols)
    plt.title('Correlation Matrix')
    plt.tight_layout()
    plt.show()


def preprocessing():
    df = pd.read_csv("dataset.csv")

    print("head of dataset:")
    print(df.head(), "\n")
    print("information of dataset and its columns:")
    print(df.info(), "\n")
    print("some statistics:")
    print(df.describe(), "\n")

    print("check for missing data")
    print(df.isna().sum())
    df = df.dropna()

    df['Target'] = df['Target'].map({'Dropout': 0, 'Graduate': 1, 'Enrolled': 2})

    plot_dataset_columns(df)
    plot_correlation_matrix(df)

    return df


def feature_selection(dataset):
    scores = mutual_info_classif(
        dataset.drop(columns='Target'),
        dataset['Target'],
        random_state=0
    )
    mi_series = pd.Series(scores, index=dataset.drop(columns='Target').columns) \
        .sort_values(ascending=False)
    top_features = mi_series.index[:10].tolist()
    print("feature selection scores:")
    print(mi_series)

    selected_columns = top_features + ['Target']
    df_selected = dataset[selected_columns]
    return df_selected


def test_train_divide(dataset):
    train_df, test_df = train_test_split(dataset, test_size=0.2, random_state=42, stratify=dataset["Target"])
    print("Train size:", len(train_df))
    print("Test size:", len(test_df))
    return train_df, test_df


def define_variables(dataset):
    linguistic_variable_list = []
    for col in dataset.columns:
        if pd.api.types.is_float_dtype(dataset[col]):
            x = LinguisticVariable(col, 0, 20)
            x.fuzzy_sets["low"] = TriangleSet(True, 0, 0, 12)
            x.fuzzy_sets["medium"] = TriangleSet(True, 11, 14, 17)
            x.fuzzy_sets["high"] = TriangleSet(True, 16, 20, 20)
            x.plot_variable()
        elif col in ["Tuition fees up to date", "Scholarship holder"]:
            x = LinguisticVariable(col, 0, 1)
            x.fuzzy_sets["YES"] = CategoricalSet(1)
            x.fuzzy_sets["NO"] = CategoricalSet(0)
        elif col == "Target":
            x = LinguisticVariable(col, 0, 2)
            x.fuzzy_sets["Dropout"] = CategoricalSet(0)
            x.fuzzy_sets["Graduate"] = CategoricalSet(1)
            x.fuzzy_sets["Enrolled"] = CategoricalSet(2)
        elif col == "Course":
            x = LinguisticVariable(col, 0, 17)
            for i in range(18):
                x.fuzzy_sets[str(i)] = CategoricalSet(i)
        else:
            x = LinguisticVariable(col, 0, 46)
            x.fuzzy_sets["low"] = TriangleSet(False, 0, 0, 16)
            x.fuzzy_sets["medium"] = TriangleSet(False, 15, 18, 22)
            x.fuzzy_sets["high"] = TriangleSet(False, 19, 46, 46)
            x.plot_variable()
        linguistic_variable_list.append(x)
    return linguistic_variable_list


def test_model(test_set, fis_model):
    y_true = []
    y_pred = []

    for _, row in test_set.iterrows():
        y_true.append(row["Target"])
        y_pred.append(fis_model.mamdani(row))

    acc = accuracy_score(y_true, y_pred)
    precision = precision_score(y_true, y_pred, average='weighted', zero_division=0)
    recall = recall_score(y_true, y_pred, average='weighted', zero_division=0)
    f1 = f1_score(y_true, y_pred, average='weighted', zero_division=0)
    cm = confusion_matrix(y_true, y_pred)

    print("Evaluation on Test Set")
    print(f"num_rules: {len(fis_model.rules)}")
    print(f"Accuracy:  {acc:.4f}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall:    {recall:.4f}")
    print(f"F1 Score:  {f1:.4f}")
    print("\nConfusion Matrix:")
    print(cm)


df = preprocessing()
df = feature_selection(df)
train_df, test_df = test_train_divide(df)
linguistic_variables = define_variables(df)
fis = FIS(train_df, linguistic_variables)
fis.wang_mendel()
print(len(fis.rules))
ga = Genetic(fis, train_df)
best_rules=ga.run()
ga.plot_genetic_accuracy()
new_fis=FIS(train_df, copy.deepcopy(linguistic_variables))
new_fis.rules=best_rules.chromosome_list
test_model(test_df, new_fis)
test_model(test_df, fis)