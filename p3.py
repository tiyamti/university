import matplotlib.pyplot as plt
import numpy as np
import matplotlib
import math

# matplotlib.use('TkAgg')


def triangular(x, a, b, c):
    if x <= a or x >= c:
        return 0
    elif a < x < b:
        return (x - a) / (b - a)
    elif b <= x < c:
        return (c - x) / (c - b)
    elif x == b:
        return 1


def trapezoidal(x, a, b, c, d):
    if x <= a or x >= d:
        return 0
    elif a < x < b:
        return (x - a) / (b - a)
    elif b <= x <= c:
        return 1
    elif c < x < d:
        return (d - x) / (d - c)


def sigmoid(x, c, a):
    value = 1 / (1 + np.exp(-a * (x - c)))
    if value == np.inf:
        return 1
    return value


def gaussian(x, m, s):
    return math.exp(-((x - m) ** 2 / (s ** 2)))


def crisp(x, a):
    return 1 if x == a else 0


fitness_functions = {
    'beginner': lambda x: triangular(x, 0, 0, 4),
    'intermediate': lambda x: triangular(x, 3, 5, 7),
    'advanced': lambda x: sigmoid(x, 7, 1.5)
}

energy_functions = {
    'low': lambda x: triangular(x, 0, 0, 3.5),
    'medium': lambda x: gaussian(x, 5, 1.5),
    'high': lambda x: sigmoid(x, 6.5, 1.2)
}

age_functions = {
    'kid': lambda x: trapezoidal(x, 0, 0, 12, 18),
    'young': lambda x: trapezoidal(x, 16, 20, 30, 35),
    'middle_aged': lambda x: trapezoidal(x, 30, 40, 50, 60),
    'old': lambda x: sigmoid(x, 65, 0.2)
}

weight_functions = {
    'underweight': lambda x: trapezoidal(x, 0, 0, 30, 45),
    'normal': lambda x: trapezoidal(x, 40, 58, 65, 75),
    'overweight': lambda x: sigmoid(x, 80, 0.25)
}

goal_functions = {
    'weight_loss': lambda x: crisp(x, 0),
    'fitness': lambda x: crisp(x, 1),
    'muscle_gain': lambda x: crisp(x, 2)
}

intensity_functions = {
    'low': lambda x: triangular(x, 0, 0, 4),
    'medium': lambda x: triangular(x, 3.5, 5, 6.5),
    'high': lambda x: triangular(x, 6, 10, 10)
}

duration_functions = {
    'short': lambda x: trapezoidal(x, 0, 0, 10, 20),
    'medium': lambda x: trapezoidal(x, 15, 25, 35, 45),
    'long': lambda x: trapezoidal(x, 40, 50, 60, 60)
}

INTENSITY_WEIGHTS = {
    'low': 1.0,
    'medium': 1.0,
    'high': 0.9
}

DURATION_WEIGHTS = {
    'short': 1.0,
    'medium': 1.0,
    'long': 0.9
}


def fuzzify(x, func_dict):
    return {label: func(x) for label, func in func_dict.items()}


def fuzzy_rules(fitness, energy, goal, age, weight, duration_wanted):
    intensity_result = {}
    duration_result = {}
    intensity_weights = INTENSITY_WEIGHTS.copy()
    duration_weights = DURATION_WEIGHTS.copy()

    if age['old'] > 0.4 or age['kid'] > 0.5:
        intensity_weights['high'] = 0.8
        duration_weights['long'] = 0.9
    if weight['underweight'] > 0.5 and age['kid'] < 0.2:
        intensity_weights['high'] = 0.8
        duration_weights['long'] = 0.8
    if duration_wanted == 0:
        duration_weights['medium'] = 0.9
        duration_weights['long'] = 0.7
    elif duration_wanted == 1:
        duration_weights['short'] = 0.9
        duration_weights['long'] = 0.9
    elif duration_wanted == 2:
        duration_weights['short'] = 0.8
        duration_weights['medium'] = 0.9
    # ----------------------------------------------------------------------------------
    # Beginner fitness & low energy → low intensity and short duration
    if fitness['beginner'] > 0 and energy['low'] > 0:
        intensity_result['low'] = max(
            intensity_result.get('low', 0),
            min(fitness['beginner'], energy['low'])
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            min(fitness['beginner'], energy['low'])
        )

    # Beginner fitness & high energy → low intensity and medium duration
    if fitness['beginner'] > 0 and energy['high'] > 0:
        intensity_result['low'] = max(
            intensity_result.get('low', 0),
            min(fitness['beginner'], energy['high'])
        )
        duration_result['medium'] = max(
            duration_result.get('medium', 0),
            min(fitness['beginner'], energy['high'])
        )

    # Advanced fitness & high energy → high intensity and long duration
    if fitness['advanced'] > 0 and energy['high'] > 0:
        intensity_result['high'] = max(
            intensity_result.get('high', 0),
            min(fitness['advanced'], energy['high'])
        )
        duration_result['long'] = max(
            duration_result.get('long', 0),
            min(fitness['advanced'], energy['high'])
        )

    # Advanced fitness but low energy → medium intensity and short duration
    if fitness['advanced'] > 0 and energy['low'] > 0:
        intensity_result['medium'] = max(
            intensity_result.get('medium', 0),
            min(fitness['advanced'], energy['low'])
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            min(fitness['advanced'], energy['low'])
        )

        # 'intermediate' fitness and 'medium' energy → medium intensity and 'medium' duration
        if fitness['intermediate'] > 0 and energy['medium'] > 0:
            intensity_result['medium'] = max(
                intensity_result.get('medium', 0),
                min(fitness['intermediate'], energy['medium'])
            )
            duration_result['medium'] = max(
                duration_result.get('medium', 0),
                min(fitness['intermediate'], energy['medium'])
            )
    # --------------------------------------------------------------------------------------------------------

    # Goal is muscle gain & fitness is intermediate → medium intensity
    if goal['muscle_gain'] > 0 and fitness['intermediate'] > 0:
        intensity_result['medium'] = max(
            intensity_result.get('medium', 0),
            min(goal['muscle_gain'], fitness['intermediate'])
        )

    # Goal is weight_loss & fitness is intermediate → high intensity
    if goal['weight_loss'] > 0 and fitness['intermediate'] > 0:
        intensity_result['high'] = max(
            intensity_result.get('high', 0),
            min(goal['weight_loss'], fitness['intermediate'])
        )

    # Goal is fitness & fitness is intermediate → medium intensity
    if goal['fitness'] > 0 and fitness['intermediate'] > 0:
        intensity_result['medium'] = max(
            intensity_result.get('medium', 0),
            min(goal['fitness'], fitness['intermediate'])
        )
    # ------------------------------------------------------------------------------------
    # Elderly with any goal → reduce intensity and duration
    if age['old'] > 0.4:
        intensity_result['low'] = max(
            intensity_result.get('low', 0),
            age['old'] * 0.5
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            age['old'] * 0.7
        )

    # kid with any goal → reduce intensity and duration
    if age['kid'] > 0.4:
        intensity_result['low'] = max(
            intensity_result.get('low', 0),
            age['kid'] * 0.7
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            age['kid'] * 0.8
        )

    # Rule 13: 'advanced' fitness & old → 'medium' intensity and short duration
    if fitness['advanced'] > 0 and age['old'] > 0:
        intensity_result['medium'] = max(
            intensity_result.get('medium', 0),
            min(fitness['advanced'], age['old'])
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            min(fitness['advanced'], age['old'])
        )
    # -------------------------------------------------------------------------------
    # Goal is weight_loss & weight is overweight → high intensity and long duration
    if goal['weight_loss'] > 0 and weight['overweight'] > 0:
        intensity_result['high'] = max(
            intensity_result.get('high', 0),
            min(goal['weight_loss'], weight['overweight'])
        )
        duration_result['long'] = max(
            duration_result.get('long', 0),
            min(goal['weight_loss'], weight['overweight'])
        )
    # Goal is weight_loss & weight is 'underweight' → low intensity and short duration
    if goal['weight_loss'] > 0 and weight['underweight'] > 0:
        intensity_result['low'] = max(
            intensity_result.get('low', 0),
            min(goal['weight_loss'], weight['underweight'])
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            min(goal['weight_loss'], weight['underweight'])
        )
    # ------------------------------------------------------------------------------------

    # Normal weight & goal is fitness →  'medium' intensity and medium duration
    if weight['normal'] > 0 and goal['fitness'] > 0:
        duration_result['medium'] = max(
            duration_result.get('medium', 0),
            min(weight['normal'], goal['fitness'])
        )

    # 'overweight' and muscle gain → 'high' intensity and short duration
    if weight['overweight'] > 0 and goal['muscle_gain'] > 0:
        intensity_result['high'] = max(
            intensity_result.get('high', 0),
            min(goal['muscle_gain'], weight['overweight'])
        )
        duration_result['short'] = max(
            duration_result.get('short', 0),
            min(weight['overweight'], goal['muscle_gain'])
        )

    # Underweight + muscle gain → medium intensity & duration
    if weight['underweight'] > 0 and goal['muscle_gain'] > 0 and energy['low'] > 0:
        intensity_result['medium'] = max(
            intensity_result.get('medium', 0),
            min(weight['underweight'], goal['muscle_gain'], energy['low'])
        )
        duration_result['medium'] = max(
            duration_result.get('medium', 0),
            min(weight['underweight'], goal['muscle_gain'], energy['low'])
        )

    for label in intensity_result:
        intensity_result[label] *= intensity_weights.get(label, 1.0)

    for label in duration_result:
        duration_result[label] *= duration_weights.get(label, 1.0)

    return intensity_result, duration_result


def defuzzify(output_membership, output_range, functions):
    numerator = 0.0
    denominator = 0.0
    for x in output_range:
        memberships = [min(value, functions[label](x)) for label, value in output_membership.items()]
        mu = max(memberships) if memberships else 0
        numerator += x * mu
        denominator += mu
    return numerator / denominator if denominator != 0 else 0

def plot_crisp_membership_crisp(goal_dict, labels, title, xlabel):
    x_vals = list(goal_dict.keys())
    y_vals = [1 for _ in x_vals]
    plt.figure(figsize=(6, 4))
    plt.bar(x_vals, y_vals, tick_label=labels, color='orange', alpha=0.7)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel("Membership Degree")
    plt.grid(axis='y')
    plt.show()

def plot_membership(func_dict, variable_range, title, xlabel):
    plt.figure(figsize=(8, 4))
    for label, func in func_dict.items():
        y_vals = [func(x) for x in variable_range]
        plt.plot(variable_range, y_vals, label=label)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel('Membership Degree')
    plt.legend()
    plt.grid(True)
    plt.show()


def plot_defuzzification(output_dict, output_func_dict, value_range, title, xlabel):
    aggregated = []
    for x in value_range:
        memberships = [min(value, output_func_dict[label](x)) for label, value in output_dict.items()]
        aggregated.append(max(memberships) if memberships else 0)
    plt.figure(figsize=(8, 4))
    plt.plot(value_range, aggregated, label='Aggregated Output', color='purple')
    plt.fill_between(value_range, 0, aggregated, color='violet', alpha=0.6)
    plt.title(f'Defuzzified Output - {title}')
    plt.xlabel(xlabel)
    plt.ylabel('Membership Degree')
    plt.grid(True)
    plt.legend()
    plt.show()


def get_user_inputs():
    print("Enter your personal information:")
    fitness_val = float(input("Fitness level (0 to 10): "))
    energy_val = float(input("Energy level (0 to 10): "))
    goal_option = input("Choose your goal: [0] Weight Loss, [1] Fitness, [2] Muscle Gain: ")
    goal_val = int(goal_option) if goal_option in ['0', '1', '2'] else 1
    age_val = float(input("Age: "))
    weight_val = float(input("Weight: "))
    duration_option = input("Choose duration: [0] short, [1] medium, [2] long ")
    duration_var = int(duration_option) if duration_option in ['0', '1', '2'] else 1
    return fitness_val, energy_val, goal_val, age_val, weight_val, duration_var


# ------------------- Main -------------------
fitness_in, energy_in, goal_in, age_in, weight_in, duration = get_user_inputs()

fitness = fuzzify(fitness_in, fitness_functions)
energy = fuzzify(energy_in, energy_functions)
goal = fuzzify(goal_in, goal_functions)
age = fuzzify(age_in, age_functions)
weight = fuzzify(weight_in, weight_functions)

intensity_output, duration_output = fuzzy_rules(fitness, energy, goal, age, weight, duration)

intensity_range = [i * 0.5 for i in range(21)]
duration_range = list(range(0, 61))

final_intensity = defuzzify(intensity_output, intensity_range, intensity_functions)
final_duration = defuzzify(duration_output, duration_range, duration_functions)

print("\nFinal Recommendation:")
print("Intensity:", round(final_intensity, 2), "/ 10")
print("Duration:", round(final_duration, 2), "minutes")

# Plot outputs
plot_defuzzification(intensity_output, intensity_functions, intensity_range, "Intensity", "Intensity (0–10)")
plot_defuzzification(duration_output, duration_functions, duration_range, "Duration", "Duration (minutes)")

plot_membership(fitness_functions, [i * 0.1 for i in range(101)], "Fitness Membership", "Fitness")
plot_membership(energy_functions, [i * 0.1 for i in range(101)], "Energy Membership", "Energy")
plot_crisp_membership_crisp(
     {0: 'weight_loss', 1: 'fitness', 2: 'muscle_gain'},
     ['Weight Loss', 'Fitness', 'Muscle Gain'],
     "Goal Membership",
     "Goal"
 )
plot_membership(age_functions, list(range(0, 81)), "Age Membership", "Age")
plot_membership(weight_functions, list(range(30, 101)), "Weight Membership", "Weight")
plot_membership(intensity_functions, intensity_range, "Intensity Output Membership", "Intensity")
plot_membership(duration_functions, duration_range, "Duration Output Membership", "Duration")
