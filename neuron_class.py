import numpy as np


class Neuron:

    def __init__(self, num_inputs, activation_func, initialization = 'he'):
        self.num_inputs = num_inputs
        # self.weights = np.random.randn(num_inputs) * 0.01
        self.activation_func = activation_func
        if initialization == 'he':
            self.weights = np.random.randn(num_inputs) * np.sqrt(2. / num_inputs)
        else:
            self.weights = np.random.randn(num_inputs) * np.sqrt(1. / num_inputs)

    @property
    def activation_func(self):
        return self._activation_func

    @activation_func.setter
    def activation_func(self, f):
        if not callable(f):
            raise ValueError("Error: this is not a function")
        self._activation_func = f

    def get_predicted_label(self, image):
        image_array = np.array(image)
        w_x_sum = np.dot(self.weights, image_array)
        return self.activation_func(w_x_sum)
