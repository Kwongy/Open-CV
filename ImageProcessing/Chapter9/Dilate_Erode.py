# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/12/4 19:20 
"""

import numpy as np
import cv2


def binaryzation_negation(image, threshold=127):
    img = image.copy()
    img[image >= threshold] = 0
    img[image < threshold] = 255
    return img


def erode(image, kernel_size=3):
    assert isinstance(kernel_size, int)
    if (kernel_size % 2 == 0) or kernel_size < 1:
        raise ValueError("kernel size must be odd and bigger than 1")
    img = np.zeros(shape=image.shape)
    start = (kernel_size - 1) // 2
    for i in range(start, image.shape[0] - kernel_size + 1):
        for j in range(start, image.shape[1] - kernel_size + 1):
            img[i, j] = np.min(image[i - start: i + start, j - start: j + start])
    return img


def dilate(image, kernel_size=3):
    assert isinstance(kernel_size, int)
    if (kernel_size % 2 == 0) or kernel_size < 1:
        raise ValueError("kernel size must be odd and bigger than 1")
    img = np.zeros(shape=image.shape)
    start = (kernel_size - 1) // 2
    for i in range(start, image.shape[0] - kernel_size + 1):
        for j in range(start, image.shape[1] - kernel_size + 1):
            img[i, j] = np.max(image[i - start: i + start, j - start: j + start])
    return img


if __name__ == "__main__":
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    img = binaryzation_negation(img)
    eroder = erode(img)
    dilater = dilate(img)
    cv2.imshow("img", img)
    cv2.imshow("erode", eroder)
    cv2.imshow("dilate", dilater)
    cv2.waitKey(0)