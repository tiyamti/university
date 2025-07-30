import math
import random

from sklearn.metrics import confusion_matrix, classification_report
from sklearn.metrics import f1_score
from neuron_class import Neuron
import preprocessing
import numpy as np


class NeuralNetwork:
    def __init__(self, num_input, num_hidden_neurons, num_output, learning_rate=0.01, epsilon=1e-7, epoch=20):
        self.hidden_neurons = []
        self.output_neurons = []

        for i in range(num_hidden_neurons):
            self.hidden_neurons.append(Neuron(num_input + 1, self.sigmoid))

        for i in range(num_output):
            self.output_neurons.append(Neuron(num_hidden_neurons + 1, lambda x: x))

        self.learning_rate = learning_rate
        self.epsilon = epsilon
        self.epoch = epoch


    def sigmoid(self, w_x_sum):
        return 1 / (1 + math.exp(-w_x_sum))

    def softmax(self, z_i):
        softmax_values = []
        sum_exp_z = 0
        for z in z_i:
            sum_exp_z += math.exp(z)
        for z in z_i:
            softmax_values.append(math.exp(z) / sum_exp_z)
        return np.array(softmax_values)

    def multi_class_cross_entropy_loss(self, y_true, y_pred):
        loss = 0
        for i in range(len(y_true)):
            loss += -(y_true[i]*math.log(y_pred[i]+self.epsilon))
        return loss

    def back_propagation_output(self, y_true, y_pred, x):
        dLoss_dw = []
        delta = y_pred - y_true
        for i in range(len(y_true)):
            grad = delta[i] * x
            dLoss_dw.append(grad)
        return np.array(dLoss_dw)

    def back_propagation_hidden(self, y_true, y_pred, y_hidden, x, hidden_index):
        sum_k = 0
        for k in range(len(y_true)):
            delta_k = y_pred[k] - y_true[k]
            weight_kj = self.output_neurons[k].weights[hidden_index]
            sum_k += delta_k * weight_kj
        sigmoid_derivative = y_hidden * (1 - y_hidden)
        dLoss = sum_k * sigmoid_derivative * x
        return dLoss

    def get_output(self, x):
        hidden_layer_outputs = []
        output_layer_z = []
        for neuron in self.hidden_neurons:
            hidden_layer_outputs.append(neuron.get_predicted_label(x))
        hidden_layer_outputs = np.append(hidden_layer_outputs, 1)
        for neuron in self.output_neurons:
            output_layer_z.append(neuron.get_predicted_label(hidden_layer_outputs))
        return self.softmax(output_layer_z)

    def gradient_decent(self, x_train, y_train):
        for epoch in range(self.epoch):
            total_loss = 0
            for x, y_true in zip(x_train, y_train):
                out_from_hidden_layer = []
                x = np.append(x, 1)

                # update output neuron weights
                y_pred = self.get_output(x)
                total_loss += self.multi_class_cross_entropy_loss(y_true, y_pred)
                for neuron in self.hidden_neurons:
                    out_from_hidden_layer.append(neuron.get_predicted_label(x))
                out_from_hidden_layer = np.append(out_from_hidden_layer, 1)
                dLoss_dwout = self.back_propagation_output(y_true, y_pred, out_from_hidden_layer)
                for i in range(len(self.output_neurons)):
                    self.output_neurons[i].weights -= self.learning_rate * dLoss_dwout[i]

                for i, neuron in enumerate(self.hidden_neurons):
                    y_hidden = neuron.get_predicted_label(x)
                    grad = self.back_propagation_hidden(y_true, y_pred, y_hidden, x, i)
                    neuron.weights -= self.learning_rate * grad
            print(f"Epoch {epoch + 1}/{self.epoch} - Loss: {total_loss / len(x_train):.4f}")

    def predict_classes(self, X):
        predictions = []
        for x in X:
            x = np.append(x, 1)
            output = self.get_output(x)
            predicted_class = np.argmax(output)
            predictions.append(predicted_class)
        return predictions


X_train, y_train = preprocessing.import_data()
y_train = preprocessing.one_hot_encode(y_train)
X_test, y_test = preprocessing.import_test()
y_test = preprocessing.one_hot_encode(y_test)

nn = NeuralNetwork(num_input=3072, num_hidden_neurons=64, num_output=10)
nn.gradient_decent(X_train, y_train)


y_pred = nn.predict_classes(X_test)

y_true = np.argmax(y_test, axis=1)

print(classification_report(y_true, y_pred))