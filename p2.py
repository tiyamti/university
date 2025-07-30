import math
from sklearn.metrics import confusion_matrix
from sklearn.metrics import f1_score
from neuron_class import Neuron
import preprocessing
import numpy as np


# import matplotlib.pyplot as plt
# import matplotlib
# matplotlib.use('TkAgg')


class NeuralNetwork:
    def __init__(self, num_input, num_hidden_neurons, learning_rate=0.01, epsilon=1e-7, epoch=20):
        self.hidden_neurons = []
        for i in range(num_hidden_neurons):
            self.hidden_neurons.append(Neuron(num_input + 1, self.sigmoid))
        self.output_neuron = Neuron(num_hidden_neurons + 1, self.sigmoid)
        self.learning_rate = learning_rate
        self.epsilon = epsilon
        self.epoch = epoch

    def sigmoid(self, w_x_sum):
        return 1 / (1 + math.exp(-w_x_sum))

    def get_output(self, x):
        hidden_layer_outputs = []
        for neuron in self.hidden_neurons:
            hidden_layer_outputs.append(neuron.get_predicted_label(x))
        hidden_layer_outputs = np.append(hidden_layer_outputs, 1)
        return self.output_neuron.get_predicted_label(hidden_layer_outputs)

    def binary_cross_entropy_loss(self, y_true, y_pred):
        return -y_true * math.log(y_pred + self.epsilon) - (1 - y_true) * math.log(1 - y_pred + self.epsilon)

    def back_propagation_output(self, y_true, y_pred, x):
        return (y_pred - y_true) * x

    def gradient_decent(self, x_train, y_train):
        for epoch in range(self.epoch):
            total_loss = 0
            indices = np.arange(len(x_train))
            np.random.shuffle(indices)
            x_train = x_train[indices]
            y_train = y_train[indices]
            for x, y_true in zip(x_train, y_train):
                out_from_hidden_layer = []
                x = np.append(x, 1)

                # update output neuron weights
                y_pred = self.get_output(x)
                total_loss += self.binary_cross_entropy_loss(y_true, y_pred)
                for neuron in self.hidden_neurons:
                    out_from_hidden_layer.append(neuron.get_predicted_label(x))
                out_from_hidden_layer = np.append(out_from_hidden_layer, 1)
                dLoss_dwout = self.back_propagation_output(y_true, y_pred, out_from_hidden_layer)
                self.output_neuron.weights = self.output_neuron.weights - self.learning_rate * dLoss_dwout

                for i, neuron in enumerate(self.hidden_neurons):
                    y_hidden = neuron.get_predicted_label(x)
                    d_hidden = y_hidden * (1 - y_hidden)
                    d_output = (y_pred - y_true)
                    grad = d_output * self.output_neuron.weights[i] * d_hidden * x
                    neuron.weights = neuron.weights - self.learning_rate * grad
            print(f"Epoch {epoch + 1}/{self.epoch} - Loss: {total_loss / len(x_train):.4f}")

    def test_network(self, x_test, y_test):
        y_pred = []
        for x in x_test:
            x = np.append(x, 1)
            output = self.get_output(x)
            y_pred.append(1 if output >= 0.5 else 0)
        cm = confusion_matrix(y_test, y_pred)
        f1 = f1_score(y_test, y_pred)
        return cm, f1


X_train, y_train = preprocessing.import_data()
y_train=preprocessing.two_class_encode(y_train)
X_test, y_test = preprocessing.import_test()
y_test=preprocessing.two_class_encode(y_test)
neural_network = NeuralNetwork(len(X_train[0]), 64)
X_train_balanced, y_train_balanced = preprocessing.balance_data(X_train, y_train)
neural_network.gradient_decent(X_train_balanced, y_train_balanced)
cm, f1 = neural_network.test_network(X_test, y_test)

print(cm)
print(f1)
