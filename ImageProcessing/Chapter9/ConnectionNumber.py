# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/12/7 19:44 
"""
# The number of connections can be used to display the state of nearby pixels

import cv2
from Dilate_Erode import binaryzation_negation
import numpy as np


def four_connection(image):
    if len(image.shape) != 2:
        raise ValueError("Images need to be grayscale")
    temp = np.zeros((image.shape[0], image.shape[1], 3), dtype=np.uint8)
    pad_img = np.pad(image // 255, (1, 1), mode="constant", constant_values=0)
    print(image.shape, pad_img.shape)
    for x in range(image.shape[0]):
        for y in range(image.shape[1]):
            if image[x, y] == 0:
                continue
            s = pad_img[x + 1, y] + pad_img[x, y + 1] + pad_img[x + 1, y + 2] + pad_img[x + 2, y + 1]
            if s == 0:
                temp[x, y] = [0, 0, 255]
            elif s == 1:
                temp[x, y] = [0, 255, 0]
            elif s == 2:
                temp[x, y] = [255, 0, 0]
            elif s == 3:
                temp[x, y] = [255, 255, 0]
            elif s == 4:
                temp[x, y] = [255, 0, 255]
    return temp


if __name__ == "__main__":
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    img = binaryzation_negation(img)
    dilater = four_connection(img)
    cv2.imshow("img", img)
    cv2.imshow("dilate", dilater)
    cv2.waitKey(0)