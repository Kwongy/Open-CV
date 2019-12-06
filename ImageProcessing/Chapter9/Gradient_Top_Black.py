# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/12/6 8:23 
"""

import cv2
import numpy as np
from Open_Close import *
from Dilate_Erode import *


def gradient(image):
    # Morphology gradient: difference of image between dilate operation and erode operation
    eroder = erode(image)
    dilater = dilate(image)
    return dilater - eroder


def top_hat(image):
    # Top hat: The difference between the original image and the resulting graph after opening
    op = opening(image)
    return image - op


def black_hat(image):
    # Black hat: The difference between the resulting graph after closing and the original image
    cls = closing(image)
    return cls - image


if __name__ == "__main__":
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    img = binaryzation_negation(img)
    image = gradient(img)
    tp = top_hat(img)
    bh = black_hat(img)
    cv2.imshow("img", image)
    cv2.imshow("tp", tp)
    cv2.imshow("bh", bh)
    cv2.waitKey(0)