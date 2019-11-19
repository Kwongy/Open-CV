# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/19 9:21 
"""

import numpy as np
import cv2


def get_impulse_noise(image, num=1000):
    img = image.copy()
    row, col = image.shape
    for i in range(num):
        x = np.random.randint(0, row)
        y = np.random.randint(0, col)
        img[x, y] = np.random.randint(0, 2) * 255
    return img


def mean_filter(image, filter_size):
    """
        filter_size must be odd and be equal or greater than 3
        remove Gaussian noise
    :param image: single channel image  w x h
    :param filter_size: either a number or tuple
    :return:
    """
    if not isinstance(filter_size, tuple):
        filter_size = (filter_size, filter_size)
    filter_template = np.ones(shape=filter_size, dtype=np.uint8)
    assert isinstance(image, np.ndarray)
    padding = int(filter_size[0] / 2)
    pad_img = np.pad(image, padding, mode="constant", constant_values=0)
    img = np.zeros(image.shape, dtype=np.uint8)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            img[i, j] = int(np.sum(filter_template * pad_img[i: i + padding * 2 + 1,
                            j: j + padding * 2 + 1]) / (filter_size[0] * filter_size[1]))
    return img


def median_filter(image, filter_size):
    """
        filter_size must be odd and be equal or greater than 3
        remove impulse noise
        This module also can change to Max or Min filter
    :param image: single channel image  w x h
    :param filter_size: either a number or tuple
    :return:
    """
    if not isinstance(filter_size, tuple):
        filter_size = (filter_size, filter_size)
    filter_template = np.ones(shape=filter_size, dtype=np.uint8)
    assert isinstance(image, np.ndarray)
    padding = int(filter_size[0] / 2)
    pad_img = np.pad(image, padding, mode="constant", constant_values=0)
    img = np.zeros(image.shape, dtype=np.uint8)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            temp = np.median(filter_template * pad_img[i: i + padding * 2 + 1,j: j + padding * 2 + 1])
            # np.max() or np.min()
            img[i, j] = temp
    return img


if __name__ == "__main__":
    image = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    image = get_impulse_noise(image)
    cv2.imshow("img", image)
    image = median_filter(image, 3)
    cv2.imshow("image", image)
    cv2.waitKey(0)