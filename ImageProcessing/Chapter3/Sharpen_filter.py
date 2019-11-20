# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/20 9:54 
"""
import numpy as np
import cv2


def laplace_sharen(image, c, laplace_filter=np.array([
                                                    [1, 1, 1],
                                                    [1, -8, 1],
                                                    [1, 1, 1]
                                                            ])):
    """
        Highlight gray transition part
    :param laplace_filter: filter
    :param image:   gray level image
    :param c:   coefficient
    :return:
    """
    assert isinstance(image, np.ndarray)
    pad_img = np.pad(image, (1, 1), mode="constant", constant_values=0)
    img = image.copy()
    n, m = image.shape
    for i in range(n):
        for j in range(m):
            temp = np.sum(laplace_filter * pad_img[i: i + 3, j: j + 3])
            img[i, j] += c * temp
    return img


def sobel_sharpen(image, c, mode="x"):
    sobel_y = np.array([[-1, 0, 1],
                        [-2, 0, 2],
                        [-1, 0, 1]])

    sobel_x = np.array([[-1, -2, -1],
                        [0, 0, 0],
                        [1, 2, 1]])
    if mode=="x":
        sobel_filter = sobel_x
    else:
        sobel_filter = sobel_y
    assert isinstance(image, np.ndarray)
    pad_img = np.pad(image, (1, 1), mode="constant", constant_values=0)
    img = image.copy()
    n, m = image.shape
    for i in range(n):
        for j in range(m):
            temp = np.sum(sobel_filter * pad_img[i: i + 3, j: j + 3])
            img[i, j] += c * temp
    return img


if __name__ == "__main__":
    image = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    cv2.imshow("img", image)
    image = sobel_sharpen(image, 1)
    cv2.imshow("image", image)
    cv2.waitKey(0)