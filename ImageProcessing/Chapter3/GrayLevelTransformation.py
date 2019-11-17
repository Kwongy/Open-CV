# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/17 8:48 
"""
import cv2
import numpy as np
img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg")


def BGR2GRAY_weightedsum(image):
    """
    :param img: 3 channel: BGR
    :return: 1 channel  gray level
    """
    Type = image.dtype
    img = image.copy()
    img[:, :, 0] = img[:, :, 0] * 0.11
    img[:, :, 1] = img[:, :, 1] * 0.59
    img[:, :, 2] = img[:, :, 2] * 0.3
    img = np.sum(img, axis=2).astype(Type)
    return img


def BGR2GRAY_meansum(image):
    """
        :param img: 3 channel: BGR
        :return: 1 channel  gray level
    """
    Type = image.dtype
    img = image.copy()
    img = np.sum(img, axis=2) / 3.0
    return img.astype(Type)


def BGR2GRAY_greenchannel(image):
    Type = image.dtype
    img = image.copy()
    img = img[:, :, 1]
    return img.astype(Type)


def Binaryzation(image, threshold):
    """
    :param image: gray level image
    """
    if len(image.shape) > 2:
        print("Input image should be gray level")
        return -1
    Type = image.dtype
    img = image.copy()
    img[img <= threshold] = 0
    img[img > threshold] = 255
    return img.astype(Type)


def Opposition(image):
    """
    :param image: gray level image
    """
    if len(image.shape) > 2:
        print("Input image should be gray level")
        return -1
    Type = image.dtype
    img = image.copy()
    img = 255 - img
    return img.astype(Type)


def Suqare(image):
    """
        :param image: gray level image
    """
    if len(image.shape) > 2:
        print("Input image should be gray level")
        return -1
    Type = image.dtype
    img = image.copy()
    img = 255.0 * (img / 255.) ** 2
    return img.astype(Type)


def LogarithmTransformation(image, v=1, c=1):
    """
    :param image: gray level image
    :return: s = clog_{v+1}(1 + v*image)
            make image brighten
    """
    if len(image.shape) > 2:
        print("Input image should be gray level")
        return -1
    Type = image.dtype
    img = image.copy() / 255.
    img = 255. * c * np.log(1 + v * img) / np.log(1 + v)    # log_{x}(y) = log_{10}(y) / log_{10}(x)
    return img.astype(Type)


def GammaTransformation(image, v=1, c=1):
    """
        :param image: gray level image
        :return: s = c * {image}^v
    """
    if len(image.shape) > 2:
        print("Input image should be gray level")
        return -1
    Type = image.dtype
    img = image.copy() / 255.
    img = 255. * c * img ** v
    return img.astype(Type)



if __name__ == "__main__":
    # img_ = BGR2GRAY_meansum(img)
    # cv2.imshow("t", img_)
    img__ = BGR2GRAY_weightedsum(img)
    cv2.imshow("h", img__)
    img_1 = GammaTransformation(img__)
    cv2.imshow("s", img_1)
    cv2.waitKey(0)