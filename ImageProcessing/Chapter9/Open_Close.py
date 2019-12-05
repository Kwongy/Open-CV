# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/12/5 8:37 
"""
import cv2
import numpy as np
from Dilate_Erode import erode, dilate, binaryzation_negation


def opening(image, N=1):
    # dilate before erode
    if len(image.shape) != 2:
        raise ValueError("Must be grayscale")
    img = image.copy()
    for i in range(N):
        img = erode(img)
    for i in range(N):
        img = dilate(img)
    return img


def closing(image, N=1):
    # erode before dilate
    if len(image.shape) != 2:
        raise ValueError("Must be grayscale")
    img = image.copy()
    for i in range(N):
        img = dilate(img)
    for i in range(N):
        img = erode(img)
    return img


if __name__ == "__main__":
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    img = binaryzation_negation(img)
    eroder = opening(img)
    dilater = closing(img)
    cv2.imshow("img", img)
    cv2.imshow("erode", eroder)
    cv2.imshow("dilate", dilater)
    cv2.waitKey(0)