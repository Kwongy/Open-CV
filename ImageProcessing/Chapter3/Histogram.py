# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/18 8:59 
"""
import cv2
import matplotlib.pyplot as plt
import numpy as np

gray_level = 256
"""
    The cumulative probability is calculated according to the numerical size,
    The cumulative probability is used to calculate the mapping value
"""


def pixel_probability(image):
    assert isinstance(image, np.ndarray)
    probability = np.zeros(shape=gray_level)
    for row in image:
        for col in row:
            probability[col] += 1
    plot(probability, "probability")
    return probability / (image.shape[0] * image.shape[1])


def probability2histogram(image):
    assert isinstance(image, np.ndarray)
    row, col = image.shape
    cumulative = np.cumsum(pixel_probability(image))       # cumulative probability
    img_map = [int(i * cumulative[i]) for i in range(gray_level)]   # transformation mapping
    img = image.copy()
    for r in range(row):
        for c in range(col):
            img[r, c] = img_map[image[r, c]]
    return img


def plot(y, name):
    plt.figure(num=name)
    plt.bar([i for i in range(gray_level)], y, width=1)
    plt.show()


if __name__ == "__main__":
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    his_img = probability2histogram(img)
    cv2.imshow("Artwork master", img)
    cv2.imshow("Histogram", his_img)
    cv2.waitKey(0)
