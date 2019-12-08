# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/12/8 19:55 
"""
import cv2
import numpy as np
import math


# Gaussian filter
def gaussian_filter(image, filter=5):
    sigma1 = sigma2 = 1
    sum = 0
    gaussian = np.zeros([filter, filter])
    for i in range(filter):
        for j in range(filter):
            gaussian[i, j] = math.exp(-1 / 2 * (np.square(i - (filter // 2) + 1) / np.square(sigma1)  # 生成二维高斯分布矩阵
                                                + (np.square(j - (filter // 2) + 1) / np.square(sigma2)))) / (
                                     2 * math.pi * sigma1 * sigma2)
            sum = sum + gaussian[i, j]

    gaussian = gaussian / sum
    W, H = image.shape
    new_gray = np.zeros([W, H])
    image = np.pad(image, (filter//2, filter//2), mode="constant", constant_values=0)
    for i in range(W):
        for j in range(H):
            new_gray[i, j] = np.sum(image[i:i + filter, j:j + filter] * gaussian)  # 与高斯矩阵卷积实现滤波
    return new_gray


# Computing the gradient
def gradient(image):
    W1, H1 = image.shape
    dx = np.zeros([W1, H1])
    dy = np.zeros([W1, H1])
    d = np.zeros([W1, H1])
    image = np.pad(image, (0, 1), 'constant', constant_values=0)
    for i in range(W1):
        for j in range(H1):
            dx[i, j] = image[i, j + 1] - image[i, j]
            dy[i, j] = image[i + 1, j] - image[i, j]
            d[i, j] = np.sqrt(np.square(dx[i, j]) + np.square(dy[i, j]))
    return dx, dy, d


# Non-Maximum Suppression
def nonmaximum_suppression(dx, dy, d):
    W2, H2 = d.shape
    NMS = np.copy(d)
    NMS[0, :] = NMS[W2 - 1, :] = NMS[:, 0] = NMS[:, H2 - 1] = 0
    for i in range(1, W2 - 1):
        for j in range(1, H2 - 1):

            if d[i, j] == 0:
                NMS[i, j] = 0
            else:
                gradX = dx[i, j]
                gradY = dy[i, j]
                gradTemp = d[i, j]

                # 如果Y方向幅度值较大
                if np.abs(gradY) > np.abs(gradX):
                    weight = np.abs(gradX) / np.abs(gradY)
                    grad2 = d[i - 1, j]
                    grad4 = d[i + 1, j]
                    # 如果x,y方向梯度符号相同
                    if gradX * gradY > 0:
                        grad1 = d[i - 1, j - 1]
                        grad3 = d[i + 1, j + 1]
                    # 如果x,y方向梯度符号相反
                    else:
                        grad1 = d[i - 1, j + 1]
                        grad3 = d[i + 1, j - 1]

                # 如果X方向幅度值较大
                else:
                    weight = np.abs(gradY) / np.abs(gradX)
                    grad2 = d[i, j - 1]
                    grad4 = d[i, j + 1]
                    # 如果x,y方向梯度符号相同
                    if gradX * gradY > 0:
                        grad1 = d[i + 1, j - 1]
                        grad3 = d[i - 1, j + 1]
                    # 如果x,y方向梯度符号相反
                    else:
                        grad1 = d[i - 1, j - 1]
                        grad3 = d[i + 1, j + 1]

                gradTemp1 = weight * grad1 + (1 - weight) * grad2
                gradTemp2 = weight * grad3 + (1 - weight) * grad4
                if gradTemp >= gradTemp1 and gradTemp >= gradTemp2:
                    NMS[i, j] = gradTemp
                else:
                    NMS[i, j] = 0
    return NMS


def canny_detection(image):
    img = gaussian_filter(image=image)
    dx, dy, d = gradient(img)
    NMS = nonmaximum_suppression(dx, dy, d)
    W3, H3 = NMS.shape
    img = np.zeros([W3, H3])
    # 定义高低阈值
    TL = 0.2 * np.max(NMS)
    TH = 0.3 * np.max(NMS)
    for i in range(1, W3 - 1):
        for j in range(1, H3 - 1):
            if (NMS[i, j] < TL):
                img[i, j] = 0
            elif (NMS[i, j] > TH):
                img[i, j] = 1
            elif ((NMS[i - 1, j - 1:j + 1] < TH).any() or (NMS[i + 1, j - 1:j + 1]).any()
                  or (NMS[i, [j - 1, j + 1]] < TH).any()):
                img[i, j] = 1
    return img


if __name__ == "__main__":
    # https://www.cnblogs.com/king-lps/p/8007134.html
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", 0)
    image = canny_detection(img)
    cv2.imshow("img", img)
    cv2.imshow("dilate", image)
    cv2.waitKey(0)
