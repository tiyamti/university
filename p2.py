#exercise 2


import matplotlib.pyplot as plt
import numpy as np



def triangular(x, a, b, c):
    if x <= a or x >= c:
        return 0
    elif a < x < b:
        return (x - a) / (b - a)
    elif b <= x < c:
        return (c - x) / (c - b)
    elif x == b:
        return 1


#رطوبت خاک
def soil_dry(x):
    return triangular(x, 0, 0, 50)

def soil_medium(x):
    return triangular(x, 30, 50, 70)

def soil_wet(x):
    return triangular(x,60, 100, 100)



#اب و هوا
def weather_sunny(x):
    return triangular(x, 0, 0, 50)

def weather_cloudy(x):
    return triangular(x, 30, 50, 70)

def weather_rainy(x):
    return triangular(x, 60, 100, 100)

#ابیاری
def water_none(x):
    return triangular(x, 0, 0, 25)

def water_low(x):
    return triangular(x, 10, 30, 50)

def water_medium(x):
    return triangular(x, 40, 60, 80)

def water_high(x):
    return triangular(x, 70, 100, 100)


import matplotlib.pyplot as plt
import numpy as np

def plot_membership(funcs, labels, title):
    x = np.linspace(0, 100, 500)
    for func, label in zip(funcs, labels):
        plt.plot(x, [func(i) for i in x], label=label)
    plt.title(title)
    plt.xlabel("Value")
    plt.ylabel("Membership Degree")
    plt.legend()
    plt.grid(True)
    plt.show()

plot_membership([soil_dry, soil_medium, soil_wet],
                ["Dry", "Medium", "Wet"], "Soil Moisture Membership Functions")

plot_membership([weather_sunny, weather_cloudy, weather_rainy],
                ["Sunny", "Cloudy", "Rainy"], "Weather Condition Membership Functions")

plot_membership([water_none, water_low, water_medium, water_high],
                ["No Water", "Low", "Medium", "High"], "Irrigation Amount Membership Functions")




def fuzzy_and(a, b):
    return min(a, b)

def rule_base(soil_val, weather_val):
    rules = []
    dry = soil_dry(soil_val)
    medium = soil_medium(soil_val)
    wet = soil_wet(soil_val)

    sunny = weather_sunny(weather_val)
    cloudy = weather_cloudy(weather_val)
    rainy = weather_rainy(weather_val)

    rules.append((fuzzy_and(dry, sunny), "High"))
    rules.append((fuzzy_and(dry, cloudy), "Medium"))
    rules.append((fuzzy_and(dry, rainy), "Low"))
    rules.append((fuzzy_and(medium, sunny), "Medium"))
    rules.append((fuzzy_and(medium, cloudy), "Low"))
    rules.append((fuzzy_and(medium, rainy), "None"))
    rules.append((fuzzy_and(wet, sunny), "None"))
    rules.append((fuzzy_and(wet, cloudy), "None"))
    rules.append((fuzzy_and(wet, rainy), "None"))

    transitional_dry_medium = min(dry, medium)
    rules.append((fuzzy_and(transitional_dry_medium, sunny), "High"))

    transitional_medium_wet = min(medium, wet)
    rules.append((fuzzy_and(transitional_medium_wet, sunny), "Low"))

    if soil_val >= 80:
        rules.append((1.0, "None"))

    return rules



def clipped_membership(func, degree):
    return lambda x: min(func(x), degree)



def centroid(aggregated_func, x_vals):
    numerator = sum(x * aggregated_func(x) for x in x_vals)
    denominator = sum(aggregated_func(x) for x in x_vals)
    return numerator / denominator if denominator != 0 else 0





def irrigation_output(soil_val, weather_val):
    rules = rule_base(soil_val, weather_val)

    output_mfs = {
        "None": water_none,
        "Low": water_low,
        "Medium": water_medium,
        "High": water_high
    }

    clipped_funcs = []
    for degree, label in rules:
        if degree > 0:
            clipped_funcs.append(clipped_membership(output_mfs[label], degree))

    def aggregated_output(x):
        return max([f(x) for f in clipped_funcs], default=0)

    x_vals = np.linspace(0, 100, 500)
    result = centroid(aggregated_output, x_vals)
    return result


def error_neg_large(x): return triangular(x, -100, -50, -20)
def error_neg_small(x): return triangular(x, -30, -10, 0)
def error_zero(x): return triangular(x, -5, 0, 5)
def error_pos_small(x): return triangular(x, 0, 10, 30)
def error_pos_large(x): return triangular(x, 20, 50, 100)

def water_none(x): return triangular(x, 0, 0, 25)
def water_low(x): return triangular(x, 10, 30, 50)
def water_medium(x): return triangular(x, 40, 60, 80)
def water_high(x): return triangular(x, 70, 100, 100)



def clipped_membership(func, degree):
    return lambda x: min(func(x), degree)

def centroid(aggregated_func, x_vals):
    numerator = sum(x * aggregated_func(x) for x in x_vals)
    denominator = sum(aggregated_func(x) for x in x_vals)
    return numerator / denominator if denominator != 0 else 0

def irrigation_fuzzy_error(error):
    rules = []
    rules.append((error_neg_large(error), "None"))
    rules.append((error_neg_small(error), "Low"))
    rules.append((error_zero(error), "None"))
    rules.append((error_pos_small(error), "Medium"))
    rules.append((error_pos_large(error), "High"))

    output_mfs = {
        "None": water_none,
        "Low": water_low,
        "Medium": water_medium,
        "High": water_high
    }

    clipped_funcs = [clipped_membership(output_mfs[label], degree)
                     for degree, label in rules if degree > 0]

    def aggregated_output(x):
        return max([f(x) for f in clipped_funcs], default=0)

    x_vals = np.linspace(0, 100, 500)
    return centroid(aggregated_output, x_vals)

def simulate_feedback_irrigation(days=10, initial_soil=15, desired_range=(40, 60)):
    weather_list = ["Sunny", "Sunny", "Cloudy", "Rainy", "Sunny", "Cloudy", "Rainy", "Sunny", "Cloudy", "Rainy"]
    weather_effect = {"Sunny": 5, "Cloudy": 2, "Rainy": -5}
    desired_mid = (desired_range[0] + desired_range[1]) / 2

    soil_history = [initial_soil]
    irrigation_history = []
    current_soil = initial_soil

    for day in range(days):
        weather = weather_list[day]
        weather_loss = weather_effect[weather]

        error = desired_mid - current_soil
        water_amount = irrigation_fuzzy_error(error)
        irrigation_history.append(water_amount)

        new_soil = current_soil + (0.097 * water_amount) - weather_loss
        new_soil = max(0, min(100, new_soil))
        soil_history.append(new_soil)
        current_soil = new_soil

    days_list = list(range(days + 1))
    irrigation_days = list(range(days))

    plt.figure(figsize=(12, 5))

    plt.subplot(1, 2, 1)
    plt.plot(days_list, soil_history, marker='o', color='green', label='Soil Moisture (%)')
    plt.axhline(desired_range[0], color='red', linestyle='--', label='Desired Range')
    plt.axhline(desired_range[1], color='red', linestyle='--')
    plt.xlabel("Day")
    plt.ylabel("Soil Moisture (%)")
    plt.title("Soil Moisture Over Time (Feedback Control)")
    plt.grid(True)
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(irrigation_days, irrigation_history, marker='o', color='blue', label='Irrigation Amount')
    plt.xlabel("Day")
    plt.ylabel("Water Given")
    plt.title("Irrigation Per Day")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.show()

    return soil_history, irrigation_history

simulate_feedback_irrigation(initial_soil=15, desired_range=(40, 60))


