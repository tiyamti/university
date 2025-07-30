import math
import random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from sklearn.metrics import classification_report
from neuron_class import Neuron
import preprocessing

matplotlib.use('TkAgg')

class NeuralNetwork:
    def __init__(self, num_input, num_hidden_neurons, num_output, activation='sigmoid', learning_rate=0.09,
                 epsilon=1e-7, epoch=3, momentum=0.9):
        self.hidden_neurons = []
        self.output_neurons = []
        self.learning_rate = learning_rate
        self.epsilon = epsilon
        self.epoch = epoch
        self.momentum = momentum
        self.loss_history = []
        self.accuracy_history = []

        if activation == 'relu':
            self.activation = self.relu
        else:
            self.activation = self.sigmoid

        init_type = 'he' if activation == 'relu' else 'xavier'

        for _ in range(num_hidden_neurons):
            self.hidden_neurons.append(Neuron(num_input + 1, self.activation, init_type))
        for _ in range(num_output):
            self.output_neurons.append(Neuron(num_hidden_neurons + 1, lambda x: x, init_type))

        self.output_velocity = [np.zeros_like(n.weights) for n in self.output_neurons]
        self.hidden_velocity = [np.zeros_like(n.weights) for n in self.hidden_neurons]

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))

    def relu(self, z):
        return np.maximum(0, z)

    def softmax(self, z):
        z = np.array(z)
        z = z - np.max(z)
        exp_scores = np.exp(z)
        sum_exp = np.sum(exp_scores)
        if sum_exp == 0 or np.isnan(sum_exp) or np.isinf(sum_exp):
            return np.ones_like(z) / len(z)
        return exp_scores / (sum_exp + self.epsilon)

    def multi_class_cross_entropy_loss(self, y_true, y_pred):
        return -np.sum(y_true * np.log(y_pred + self.epsilon))

    def back_propagation_output(self, y_true, y_pred, x):
        delta = y_pred - y_true
        return np.array([delta[i] * x for i in range(len(y_true))])

    def back_propagation_hidden(self, y_true, y_pred, y_hidden, x, hidden_index):
        sum_k = 0
        for k in range(len(y_true)):
            delta_k = y_pred[k] - y_true[k]
            weight_kj = self.output_neurons[k].weights[hidden_index]
            sum_k += delta_k * weight_kj
        if self.activation == self.relu:
            derivative = 1.0 if y_hidden > 0 else 0.0
        else:
            derivative = y_hidden * (1 - y_hidden)
        return sum_k * derivative * x

    def get_output(self, x_with_bias):
        hidden_outputs = [n.get_predicted_label(x_with_bias) for n in self.hidden_neurons]
        hidden_outputs_with_bias = np.append(hidden_outputs, 1)
        output_z = [n.get_predicted_label(hidden_outputs_with_bias) for n in self.output_neurons]
        return self.softmax(output_z)

    def train(self, x_train, y_train, optimizer='momentum'):
        for epoch in range(self.epoch):
            total_loss = 0
            correct = 0
            for x, y_true in zip(x_train, y_train):
                x_with_bias = np.append(x, 1)
                y_pred = self.get_output(x_with_bias)
                total_loss += self.multi_class_cross_entropy_loss(y_true, y_pred)

                if np.argmax(y_pred) == np.argmax(y_true):
                    correct += 1

                hidden_outputs = [n.get_predicted_label(x_with_bias) for n in self.hidden_neurons]
                hidden_outputs_with_bias = np.append(hidden_outputs, 1)

                dL_dw_out = self.back_propagation_output(y_true, y_pred, hidden_outputs_with_bias)
                for i, neuron in enumerate(self.output_neurons):
                    grad = dL_dw_out[i]
                    if optimizer == 'momentum':
                        self.output_velocity[i] = self.learning_rate * grad + self.momentum * self.output_velocity[i]
                        neuron.weights -= self.output_velocity[i]
                    else:
                        neuron.weights -= self.learning_rate * grad

                for i, neuron in enumerate(self.hidden_neurons):
                    y_hidden = neuron.get_predicted_label(x_with_bias)
                    grad = self.back_propagation_hidden(y_true, y_pred, y_hidden, x_with_bias, i)
                    if optimizer == 'momentum':
                        self.hidden_velocity[i] = self.learning_rate * grad + self.momentum * self.hidden_velocity[i]
                        neuron.weights -= self.hidden_velocity[i]
                    else:
                        neuron.weights -= self.learning_rate * grad

            avg_loss = total_loss / len(x_train)
            accuracy = correct / len(x_train)
            self.loss_history.append(avg_loss)
            self.accuracy_history.append(accuracy)
            print(f"Epoch {epoch + 1}/{self.epoch} - Loss: {avg_loss:.4f} - Accuracy: {accuracy * 100:.2f}%")

    def predict_classes(self, X):
        predictions = []
        for x in X:
            x_with_bias = np.append(x, 1)
            output = self.get_output(x_with_bias)
            predictions.append(np.argmax(output))
        return predictions

    def plot_learning_curve(self, label="Model"):
        plt.figure(figsize=(12, 5))
        plt.subplot(1, 2, 1)
        plt.plot(self.loss_history, label=f"{label} - Loss")
        plt.xlabel("Epoch")
        plt.ylabel("Loss")
        plt.legend()
        plt.subplot(1, 2, 2)
        plt.plot(self.accuracy_history, label=f"{label} - Accuracy")
        plt.xlabel("Epoch")
        plt.ylabel("Accuracy")
        plt.legend()
        plt.show()


# Load data
X_train, y_train = preprocessing.import_data()
X_test, y_test = preprocessing.import_test()
y_train = preprocessing.one_hot_encode(y_train)
y_test = preprocessing.one_hot_encode(y_test)

# Model with ReLU + Momentum
nn_relu_momentum = NeuralNetwork(3072, 64, 10, activation='relu')
nn_relu_momentum.train(X_train, y_train, optimizer='momentum')
nn_relu_momentum.plot_learning_curve(label="ReLU + Momentum")

# Model with Sigmoid + Gradient Descent
nn_sigmoid_gd = NeuralNetwork(3072, 64, 10, activation='sigmoid')
nn_sigmoid_gd.train(X_train, y_train, optimizer='gd')
nn_sigmoid_gd.plot_learning_curve(label="Sigmoid + Gradient Descent")

# Evaluation
y_pred = nn_relu_momentum.predict_classes(X_test)
y_true = np.argmax(y_test, axis=1)
print(classification_report(y_true, y_pred))
