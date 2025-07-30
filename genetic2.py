import random
from random import sample
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('TkAgg')
import pandas as pd


class GeneticAlgorithm:
    def __init__(self, train_set, num_of_features, population_size=5, genome_length=9, mutation_rate=0.6,
                 crossover_rate=0.9, generations=50, patience=10):
        self.patience = patience
        self.num_of_features = num_of_features
        self.train_set = train_set.sample(frac=0.2)
        self.population_size = population_size
        self.genome_length = genome_length
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.generations = generations
        self.population = self.init_population()
        self.feature_selection_history = []
        self.accuracy_history = []

    def random_genome(self):
        chromosome = np.zeros(9)
        features = sample(range(0, 9), self.num_of_features)
        for feature in features:
            chromosome[feature] = 1
        return chromosome

    def init_population(self):
        return [self.random_genome() for _ in range(self.population_size)]

    def prepare_data_for_fitness(self, chromosome):

        selected_features = [i for i, gene in enumerate(chromosome) if gene == 1]
        if not selected_features:
            return 0

        x = self.train_set.values[:, selected_features]
        y = self.train_set.values[:, 9]
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=100)
        return x_train, x_test, y_train, y_test

    def fitness(self, chromosome):
        x_train, x_test, y_train, y_test = self.prepare_data_for_fitness(chromosome)
        model = DecisionTreeClassifier(random_state=42, max_depth=10)
        model.fit(x_train, y_train)
        y_pred = model.predict(x_test)
        return accuracy_score(y_test, y_pred)

    def tournament_selection(self, fitness_scores, k=3):
        selected = random.sample(list(enumerate(fitness_scores)), k)
        winner = max(selected, key=lambda x: x[1])
        return self.population[winner[0]]

    def roulette_wheel_selection(self, fitness_scores):
        total_fitness = sum(fitness_scores)
        probabilities = [f / total_fitness for f in fitness_scores]
        selected_index = np.random.choice(len(self.population), p=probabilities)
        return self.population[selected_index]

    def rank_based_selection(self, fitness_scores):
        sorted_indices = np.argsort(fitness_scores)
        ranks = np.arange(1, len(self.population) + 1)
        probabilities = ranks / sum(ranks)
        selected_index = np.random.choice(sorted_indices, p=probabilities)
        return self.population[selected_index]

    def multi_point_crossover(self, parent1, parent2, num_points=2):
        points = sorted(random.sample(range(1, len(parent1)), num_points))
        child1, child2 = parent1[:], parent2[:]
        for i in range(len(points)):
            if i % 2 == 0:
                child1[points[i]:], child2[points[i]:] = child2[points[i]:], child1[points[i]:]
        return child1, child2

    def uniform_crossover(self, parent1, parent2):
        child1, child2 = parent1[:], parent2[:]
        for i in range(len(parent1)):
            if random.random() < 0.5:
                child1[i], child2[i] = child2[i], child1[i]
        return child1, child2

    def Counter_based_crossover(self, parent1, parent2):
        child = [np.zeros(9), np.zeros(9)]
        for j in range(2):
            counter_one_child1 = 0
            counter_zero_child1 = 0
            for i in range(self.genome_length):
                if counter_one_child1 == self.num_of_features:
                    child[j][i] = 0
                elif counter_zero_child1 == self.genome_length - self.num_of_features:
                    child[j][i] = 1
                else:
                    child[j][i] = random.choice((parent1[i], parent2[i]))
                    if child[j][i] == 0:
                        counter_zero_child1 += 1
                    else:
                        counter_one_child1 += 1
        child1, child2 = child
        return child1, child2

    def Map_of_ones_crossover(self, parent1, parent2):
        child = [np.zeros(9), np.zeros(9)]
        for i in range(2):
            pos1_p1 = [i for i, gene in enumerate(parent1) if gene == 1]
            pos1_p2 = [i for i, gene in enumerate(parent1) if gene == 1]
            for j in range(self.num_of_features):
                random_parent = random.choice((parent1, parent2))
                if (random_parent == parent1).all():
                    random_pos = random.choice(pos1_p1)
                else:
                    random_pos = random.choice(pos1_p2)
                child[i][random_pos] = 1
                try:
                    pos1_p1.remove(random_pos)
                    pos1_p2.remove(random_pos)
                except Exception:
                    print("not found")
        child1, child2 = child
        return child1, child2

    def mutation(self, chromosome):
        for i in range(len(chromosome)):
            if random.random() < self.mutation_rate:
                chromosome[i] = 1 - chromosome[i]
        return chromosome

    def swap_mutation(self, chromosome):
        if random.random() < self.mutation_rate:
            pos1, pos2 = random.sample(range(len(chromosome)), 2)
            chromosome[pos1], chromosome[pos2] = chromosome[pos2], chromosome[pos1]
        return chromosome

    def stopping_criteria(self, generation, best_fitness, last_best_fitness):
        if generation >= self.generations:
            return True
        if abs(best_fitness - last_best_fitness) < 0.001:
            self.patience -= 1
            if self.patience == 0:
                return True
        else:
            self.patience=10
        return False

    def run(self, selection_method, crossover_method):
        print("Genetic Algorithm Running...")
        fitness_scores = [self.fitness(ch) for ch in self.population]
        best_fitness = max(fitness_scores)
        for generation in range(self.generations):
            new_population = []
            for _ in range(self.population_size // 2):
                parent1 = selection_method(fitness_scores)
                parent2 = selection_method(fitness_scores)
                if random.random() < self.crossover_rate:
                    child1, child2 = crossover_method(parent1, parent2)
                else:
                    child1, child2 = parent1[:], parent2[:]
                new_population.append(self.swap_mutation(child1))
                new_population.append(self.swap_mutation(child2))
            print(max(fitness_scores))
            last_best_fitness = best_fitness

            selected_features_per_generation = [
                [i for i, gene in enumerate(chromosome) if gene == 1] for chromosome in new_population]
            self.feature_selection_history.append(selected_features_per_generation)
            self.accuracy_history.append(best_fitness)

            self.population = new_population
            fitness_scores = [self.fitness(ch) for ch in self.population]
            best_fitness = max(fitness_scores)
            if self.stopping_criteria(generation, best_fitness, last_best_fitness):
                break
        print("Genetic Algorithm Completed.")
        return self.population[np.argmax(fitness_scores)]

    def plot_feature_selection_distribution(self):
        plt.figure(figsize=(10, 6))
        for generation, selected_features in enumerate(self.feature_selection_history):
            for features in selected_features:
                for feature in features:
                    plt.scatter(generation, feature, c='blue', alpha=0.5)

        plt.title('Feature Selection Distribution Across Generations')
        plt.xlabel('Generation Number')
        plt.ylabel('Feature Index')
        plt.show()

    def plot_accuracy_comparison(self):
        plt.figure(figsize=(10, 6))
        plt.plot(range(len(self.accuracy_history)), self.accuracy_history, marker='o', color='green')
        plt.title('Accuracy Comparison Over Generations')
        plt.xlabel('Generation Number')
        plt.ylabel('Accuracy')
        plt.show()


def import_dataset():
    # read train data
    train_dataset = pd.read_csv("Train.csv")
    train_dataset.drop('ID', inplace=True, axis=1)
    # control missing data
    train_dataset.dropna(
        subset=['Gender', 'Age', 'Profession', 'Family_Size', 'Var_1', 'Spending_Score', 'Graduated', 'Ever_Married'],
        inplace=True)
    train_dataset['Work_Experience'] = train_dataset.apply(lambda row: missing_value_control(row, train_dataset),
                                                           axis=1)
    # encoding data
    encoding_categories(train_dataset)
    # remove outliers
    remove_Outliers(train_dataset)

    test_dataset = pd.read_csv("Test.csv")
    test_dataset.drop('ID', inplace=True, axis=1)
    test_dataset.dropna(inplace=True)
    encoding_categories(test_dataset)
    return train_dataset, test_dataset


def encoding_categories(dataset):
    label_encoder = preprocessing.LabelEncoder()
    dataset['Gender'] = label_encoder.fit_transform(dataset['Gender'])
    dataset['Ever_Married'] = label_encoder.fit_transform(dataset['Ever_Married'])
    dataset['Graduated'] = label_encoder.fit_transform(dataset['Graduated'])
    dataset['Profession'] = label_encoder.fit_transform(dataset['Profession'])
    dataset['Spending_Score'] = label_encoder.fit_transform(dataset['Spending_Score'])
    dataset['Var_1'] = label_encoder.fit_transform(dataset['Var_1'])
    dataset['Segmentation'] = label_encoder.fit_transform(dataset['Segmentation'])


def missing_value_control(row, dataset, age_range=6):
    if np.isnan(row['Work_Experience']):
        lower_bound = row['Age'] - (age_range // 2)
        upper_bound = row['Age'] + (age_range // 2)

        similar_ages = dataset[(dataset['Age'] >= lower_bound) & (dataset['Age'] <= upper_bound) & dataset[
            'Work_Experience'].notna()]

        if not similar_ages.empty:
            return similar_ages['Work_Experience'].mean()
        else:
            return dataset['Work_Experience'].mean()
    return row['Work_Experience']


def remove_Outliers(dataset):
    Q1 = dataset.quantile(0.25)
    Q3 = dataset.quantile(0.75)
    IQR = Q3 - Q1

    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR

    dataset[(dataset >= lower_bound) & (dataset <= upper_bound)].dropna(inplace=True)


def check_DecisionTreeClassifier(train_set, test_set, features):
    selected_features = [i for i, gene in enumerate(features) if gene == 1]
    if not selected_features:
        return 0
    x_train = train_set.values[:, selected_features]
    y_train = train_set.values[:, 9]
    x_test = test_set.values[:, selected_features]
    y_test = test_set.values[:, 9]
    model = DecisionTreeClassifier(random_state=42, max_depth=10)
    model.fit(x_train, y_train)
    y_pred = model.predict(x_test)
    return accuracy_score(y_test, y_pred)


if __name__ == "__main__":
    train_set, test_set = import_dataset()

    ga = GeneticAlgorithm(train_set, 3)

    selection_methods = {"1": ga.tournament_selection, "2": ga.roulette_wheel_selection, "3": ga.rank_based_selection}
    crossover_methods = {"1": ga.Counter_based_crossover, "2": ga.Map_of_ones_crossover}

    print("Select Selection Method:\n1. Tournament Selection\n2. Roulette Wheel Selection\n3. Rank-Based Selection")
    selection_choice = input("Enter choice: ")

    print("Select Crossover Method:\n1. Counter_based_crossover\n2. Map_of_ones_crossover")
    crossover_choice = input("Enter choice: ")

    features = ga.run(selection_methods[selection_choice], crossover_methods[crossover_choice])
    print(features)
    print(check_DecisionTreeClassifier(train_set, test_set, features))
    ga.plot_feature_selection_distribution()
    ga.plot_accuracy_comparison()
    print(check_DecisionTreeClassifier(train_set, test_set, [1,1,1,1,1,1,1,1,1]))
