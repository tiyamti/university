import math
import numpy as np
from sklearn.metrics import confusion_matrix, f1_score, classification_report
from neuron2 import Neuron
import preprocessing
import matplotlib

matplotlib.use('TkAgg')


class NeuralNetwork:
    def __init__(self, num_input, hidden_layers_info, num_class, batch_size=100, learning_rate=0.1, epsilon=1e-7,
                 epoch=20, momentum_gamma=0.9, ha_wight=False):
        self.hidden_layers = []
        self.output_neurons = []
        self.learning_rate = learning_rate
        self.epsilon = epsilon
        self.epoch = epoch
        self.num_class = num_class
        self.momentum_gamma = momentum_gamma
        self.velocities_hidden = []
        self.velocities_output = []
        self.batch_size = batch_size
        self.loss_history = []
        self.accuracy_history = []

        for layer_num in range(len(hidden_layers_info)):
            layer = []
            input_size = num_input if layer_num == 0 else hidden_layers_info[layer_num - 1][0]
            for _ in range(hidden_layers_info[layer_num][0]):
                layer.append(Neuron(input_size, hidden_layers_info[layer_num][1], hidden_layers_info[layer_num][2], ha_wight))
            self.hidden_layers.append(layer)
            self.velocities_hidden.append([np.zeros_like(neuron.weights) for neuron in layer])

        output_input_size = num_input if len(self.hidden_layers) == 0 else hidden_layers_info[-1][0]

        if num_class == 1:
            self.output_neurons.append(
                Neuron(output_input_size, self.sigmoid, self.sigmoid_derivative, ha_wight))
            self.velocities_output = [np.zeros_like(self.output_neurons[0].weights)]
        else:
            for _ in range(num_class):
                self.output_neurons.append(
                    Neuron(output_input_size, lambda x: x, lambda x: 1, ha_wight))
            self.velocities_output = [np.zeros_like(neuron.weights) for neuron in self.output_neurons]

    @staticmethod
    def sigmoid(x):
        x = np.clip(x, -500, 500)
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def sigmoid_derivative(x):
        s = NeuralNetwork.sigmoid(x)
        return s * (1 - s)

    @staticmethod
    def relu(x):
        return np.maximum(0, x)

    @staticmethod
    def relu_derivative(x):
        return (x > 0).astype(float)

    def softmax(self, z_i):
        z_i = np.clip(z_i, -500, 500)
        exp_z = np.exp(z_i - np.max(z_i))
        sum_exp_z = np.sum(exp_z)
        return exp_z / sum_exp_z

    def get_output(self, x):
        input_for_layers = [x]
        z_layers = []

        for layer in self.hidden_layers:
            hidden_output = [neuron.get_predicted_label(input_for_layers[-1]) for neuron in layer]
            z_layer = [neuron.get_z(input_for_layers[-1]) for neuron in layer]
            input_for_layers.append(hidden_output)
            z_layers.append(z_layer)

        output_input = input_for_layers[-1]
        output_z = [neuron.get_z(output_input) for neuron in self.output_neurons]
        z_layers.append(output_z)

        if self.num_class == 1:
            output = self.sigmoid(output_z[0])
        else:
            output = self.softmax(output_z)

        return output, input_for_layers, z_layers

    def multi_class_cross_entropy_loss(self, y_true, y_pred):
        if self.num_class == 1:
            y_true = y_true[0] if isinstance(y_true, (list, np.ndarray)) else y_true
            y_pred = y_pred[0] if isinstance(y_pred, (list, np.ndarray)) else y_pred
            return -(y_true * math.log(y_pred + self.epsilon) +
                     (1 - y_true) * math.log(1 - y_pred + self.epsilon))
        else:
            return -np.sum(y_true * np.log(y_pred + self.epsilon))

    def backpropagation(self, x, y_true):
        y_pred, _, z_layers = self.get_output(x)
        deltas = [None] * (len(self.hidden_layers) + 1)

        if self.num_class == 1:
            y_val = y_true[0] if isinstance(y_true, (list, np.ndarray)) else y_true
            deltas[-1] = np.array([y_pred - y_val])
        else:
            deltas[-1] = y_pred - y_true

        for l in reversed(range(len(self.hidden_layers))):
            delta_next = deltas[l + 1]
            weights_next = np.array([n.weights for n in (
                self.output_neurons if l == len(self.hidden_layers) - 1 else self.hidden_layers[l + 1])])
            delta_current = []

            for j, neuron in enumerate(self.hidden_layers[l]):
                z = z_layers[l][j]
                g_prime = neuron.differential_activation(z)
                error = np.dot(weights_next[:, j], delta_next)
                delta_current.append(error * g_prime)

            deltas[l] = np.array(delta_current)

        return deltas

    def make_batches(self, x_train, y_train):
        return [(x_train[i:i + self.batch_size], y_train[i:i + self.batch_size])
                for i in range(0, len(x_train), self.batch_size)]

    def check_early_stopping(self, avg_loss, best_loss, epochs_without_improvement, min_delta, patience):
        if best_loss - avg_loss > min_delta:
            return False, avg_loss, 0
        else:
            return epochs_without_improvement + 1 >= patience, best_loss, epochs_without_improvement + 1

    def train(self, x_train, y_train, optimizer=None, patience=5, min_delta=1e-4):
        self.loss_history = []
        self.accuracy_history = []

        if optimizer is None:
            optimizer = self.gradient_descent

        best_loss = float('inf')
        epochs_without_improvement = 0

        for epoch in range(self.epoch):
            total_loss = 0
            batches = self.make_batches(x_train, y_train)

            for x_batch, y_batch in batches:
                grad_output = [np.zeros_like(neuron.weights) for neuron in self.output_neurons]
                grad_hidden = [[np.zeros_like(neuron.weights) for neuron in layer] for layer in self.hidden_layers]

                batch_loss = 0
                for x, y_true in zip(x_batch, y_batch):
                    y_pred, input_for_layers, _ = self.get_output(x)
                    batch_loss += self.multi_class_cross_entropy_loss(y_true, y_pred)
                    deltas = self.backpropagation(x, y_true)

                    output_input = np.append(input_for_layers[-1], 1)
                    for i, neuron in enumerate(self.output_neurons):
                        grad_output[i] += deltas[-1][i] * output_input

                    for l, layer in enumerate(self.hidden_layers):
                        hidden_input = np.append(input_for_layers[l], 1)
                        for j, neuron in enumerate(layer):
                            grad_hidden[l][j] += deltas[l][j] * hidden_input

                for i, neuron in enumerate(self.output_neurons):
                    neuron.weights -= optimizer(grad_output[i] / len(x_batch), layer='output', idx=i)

                for l, layer in enumerate(self.hidden_layers):
                    for j, neuron in enumerate(layer):
                        neuron.weights -= optimizer(grad_hidden[l][j] / len(x_batch),
                                                    layer='hidden', layer_idx=l, idx=j)

                total_loss += batch_loss

            avg_loss = total_loss / len(x_train)
            self.loss_history.append(avg_loss)

            correct = 0
            for x, y in zip(x_train, y_train):
                output, _, _ = self.get_output(x)
                if self.num_class == 1:
                    pred = 1 if output.item() >= 0.5 else 0
                    true = int(y)
                else:
                    pred = np.argmax(output)
                    true = np.argmax(y)
                correct += (pred == true)

            accuracy = correct / len(x_train)
            self.accuracy_history.append(accuracy)
            print(f"Epoch {epoch + 1}/{self.epoch} - Loss: {avg_loss:.4f} - Accuracy: {accuracy:.4f}")

            should_stop, best_loss, epochs_without_improvement = self.check_early_stopping(
                avg_loss, best_loss, epochs_without_improvement, min_delta, patience)
            if should_stop:
                print(f"Early stopping triggered at epoch {epoch + 1}")
                break

    def gradient_descent(self, gradient, **kwargs):
        return self.learning_rate * gradient

    def momentum(self, gradient, **kwargs):
        layer = kwargs.get('layer', None)
        layer_idx = kwargs.get('layer_idx', None)
        idx = kwargs.get('idx', None)

        if layer == 'output':
            v = self.velocities_output[idx]
            v_new = self.momentum_gamma * v + self.learning_rate * gradient
            self.velocities_output[idx] = v_new
            return v_new
        elif layer == 'hidden':
            v = self.velocities_hidden[layer_idx][idx]
            v_new = self.momentum_gamma * v + self.learning_rate * gradient
            self.velocities_hidden[layer_idx][idx] = v_new
            return v_new
        else:
            return self.learning_rate * gradient

    def test_network(self, x_test, y_test):
        y_pred = []
        for x in x_test:
            output, _, _ = self.get_output(x)
            if self.num_class == 1:
                pred = 1 if output.item() >= 0.5 else 0
            else:
                pred = np.argmax(output)
            y_pred.append(pred)

        y_true_labels = [int(y) if self.num_class == 1 else np.argmax(y) for y in y_test]
        cm = confusion_matrix(y_true_labels, y_pred)
        f1 = f1_score(y_true_labels, y_pred, average='macro')
        c = classification_report(y_true_labels, y_pred)  # ← fixed here
        self.plot_loss()
        self.plot_accuracy()
        return cm, f1, c

    def plot_loss(self):
        import matplotlib.pyplot as plt
        plt.plot(self.loss_history, label="Loss", color="blue")
        plt.xlabel("Epoch")
        plt.ylabel("Loss")
        plt.title("Training Loss Over Epochs")
        plt.legend()
        plt.grid(True)
        plt.show()

    def plot_accuracy(self):
        import matplotlib.pyplot as plt
        plt.plot(self.accuracy_history, label="Accuracy", color="green")
        plt.xlabel("Epoch")
        plt.ylabel("Accuracy")
        plt.title("Training Accuracy Over Epochs")
        plt.legend()
        plt.grid(True)
        plt.show()


X_train, y_train = preprocessing.import_data()
y_train = preprocessing.two_class_encode(y_train)
X_test, y_test = preprocessing.import_test()
y_test = preprocessing.two_class_encode(y_test)

# part1- only one neuron
hidden_single_class_nn = NeuralNetwork(len(X_train[0]), [], 1)
hidden_single_class_nn.train(X_train, y_train, optimizer=hidden_single_class_nn.gradient_descent)
cm, f1, c = hidden_single_class_nn.test_network(X_test, y_test)
print(cm)
print(f1)
print(c)

# part2- 64 hidden neuron and single class
hidden_single_class_nn = NeuralNetwork(len(X_train[0]), [(64, NeuralNetwork.sigmoid, NeuralNetwork.sigmoid_derivative)], 1, epoch=10)
hidden_single_class_nn.train(X_train, y_train, optimizer=hidden_single_class_nn.gradient_descent)
cm, f1, c = hidden_single_class_nn.test_network(X_test, y_test)
print(cm)
print(f1)
print(c)

# part3- 64 hidden neuron multiple class
X_train, y_train = preprocessing.import_data()
y_train = preprocessing.one_hot_encode(y_train)
X_test, y_test = preprocessing.import_test()
y_test = preprocessing.one_hot_encode(y_test)

hidden_single_class_nn_momentum = NeuralNetwork(len(X_train[0]), [(64, NeuralNetwork.sigmoid, NeuralNetwork.sigmoid_derivative)], 10, epoch=8)
hidden_single_class_nn_momentum.train(X_train, y_train, optimizer=hidden_single_class_nn_momentum.gradient_descent)
cm, f1, c = hidden_single_class_nn_momentum.test_network(X_test, y_test)
print(cm)
print(f1)
print(c)

# part4- 64 hidden neuron multiple class with momentum
hidden_single_class_nn_momentum = NeuralNetwork(len(X_train[0]), [(64, NeuralNetwork.sigmoid, NeuralNetwork.sigmoid_derivative)], 10, epoch=8)
hidden_single_class_nn_momentum.train(X_train, y_train, optimizer=hidden_single_class_nn_momentum.momentum)
cm, f1, c = hidden_single_class_nn_momentum.test_network(X_test, y_test)
print(cm)
print(f1)
print(c)

# part4- 64 hidden neuron multiple class with ReLU
hidden_single_class_nn_momentum = NeuralNetwork(len(X_train[0]), [(64, NeuralNetwork.relu, NeuralNetwork.relu_derivative)], 10, epoch=8, ha_wight=True)
hidden_single_class_nn_momentum.train(X_train, y_train, optimizer=hidden_single_class_nn_momentum.momentum)
cm, f1, c = hidden_single_class_nn_momentum.test_network(X_test, y_test)
print(cm)
print(f1)
print(c)

