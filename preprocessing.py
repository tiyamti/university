import pickle
import numpy as np


def import_data():
    paths = ['.\\cifar-100 dataset\\data_batch_1', '.\\cifar-100 dataset\\data_batch_2',
             '.\\cifar-100 dataset\\data_batch_3', '.\\cifar-100 dataset\\data_batch_4',
             '.\\cifar-100 dataset\\data_batch_5']
    images = []
    labels = []
    for path in paths:
        with open(path, 'rb') as fo:
            dict = pickle.load(fo, encoding='bytes')
            images.extend(dict[b'data'])
            labels.extend(dict[b'labels'])
    # scaling
    images = np.array(images) / 255.0
    return images, labels


def import_test():
    with open('.\\cifar-100 dataset\\test_batch', 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
        images = dict[b'data']
        labels = dict[b'labels']
    # scaling
    images = np.array(images) / 255.0
    return images, labels


def two_class_encode(labels):
    binary_labels = []
    for label in labels:
        if label == 0:
            binary_labels.append(1)
        else:
            binary_labels.append(0)
    return binary_labels


def one_hot_encode(labels, num_class=10):
    one_hot_labels = []
    for label in labels:
        one_hot_label = np.zeros(num_class)
        one_hot_label[label]=1
        one_hot_labels.append(one_hot_label)
    return one_hot_labels



def balance_data(x, y):
    x = np.array(x)
    y = np.array(y)

    x1 = x[y == 1]
    y1 = y[y == 1]
    x0 = x[y == 0]
    y0 = y[y == 0]

    x0 = x0[:len(x1)]
    y0 = y0[:len(y1)]

    x_balanced = np.concatenate([x0, x1])
    y_balanced = np.concatenate([y0, y1])
    indices = np.arange(len(x_balanced))
    np.random.shuffle(indices)

    return x_balanced[indices], y_balanced[indices]
