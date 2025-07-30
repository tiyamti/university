import numpy as np


class Neuron:

    def __init__(self, num_inputs, activation_func, differential_activation, ha_weight=False):
        if ha_weight:
            self.weights = np.random.randn(num_inputs+1) * np.sqrt(2. / num_inputs)
        else:
            self.weights = np.random.randn(num_inputs+1) * 0.01
        self.activation_func = activation_func
        self.differential_activation = differential_activation

    @property
    def activation_func(self):
        return self._activation_func

    @activation_func.setter
    def activation_func(self, f):
        if not callable(f):
            raise ValueError("Error: this is not a function")
        self._activation_func = f

    @property
    def differential_activation(self):
        return self._differential_activation

    @differential_activation.setter
    def differential_activation(self, f):
        if not callable(f):
            raise ValueError("Error: this is not a function")
        self._differential_activation = f

    def get_predicted_label(self, x):
        z = self.get_z(x)
        return self.activation_func(z)

    def get_z(self, x):
        x=np.append(x, 1)
        return np.dot(self.weights, x)