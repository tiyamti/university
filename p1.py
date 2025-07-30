import preprocessing
import math
from sklearn.metrics import confusion_matrix
from sklearn.metrics import f1_score
from neuron_class import Neuron
import numpy as np



class NeuralNetwork:
    def __init__(self, neuron, learning_rate=0.01, epsilon=1e-7, epoch=8):
        self.neuron = neuron
        self.learning_rate = learning_rate
        self.epsilon = epsilon
        self.epoch=epoch

    def binary_cross_entropy_loss(self, y_true, y_pred):
        return -y_true * math.log(y_pred + self.epsilon) - (1 - y_true) * math.log(1 - y_pred + self.epsilon)

    def back_propagation(self, y_true, y_pred, x):
        return (y_pred - y_true) * x

    def gradient_decent(self, x_train, y_train):
        for i in range(self.epoch):
            for x, y_true in zip(x_train, y_train):
                x = np.append(x, 1)
                y_pred = self.neuron.get_predicted_label(x)
                dLoss_dw = self.back_propagation(y_true, y_pred, x)
                self.neuron.weights = self.neuron.weights - self.learning_rate * dLoss_dw

    def test_network(self, x_test, y_test):
        y_pred = []
        for x in x_test:
            x = np.append(x, 1)
            output = self.neuron.get_predicted_label(x)
            y_pred.append(1 if output >= 0.5 else 0)
        cm = confusion_matrix(y_test, y_pred)
        f1 = f1_score(y_test, y_pred)
        return cm, f1


def sigmoid(w_x_sum):
    return 1 / (1 + math.exp(-w_x_sum))


X_train, y_train = preprocessing.import_data()
y_train=preprocessing.two_class_encode(y_train)
X_test, y_test = preprocessing.import_test()
y_test=preprocessing.two_class_encode(y_test)
neuron = Neuron(len(X_train[0])+1, sigmoid)
neural_network = NeuralNetwork(neuron)
neural_network.gradient_decent(X_train, y_train)
cm, f1 = neural_network.test_network(X_test, y_test)
print(cm)
print(f1)
