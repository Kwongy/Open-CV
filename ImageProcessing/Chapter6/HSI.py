# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/29 20:47 
"""

import cv2
import numpy as np


def RGB2HSI(image):
    B, G, R = cv2.split(image / 255.)
    row, col = B.shape
    H = np.zeros((row, col))
    I = (R + B + G) / 3.
    S = np.zeros((row, col))
    for i in range(row):
        for j in range(col):
            temp = B[i, j] + R[i, j] + G[i, j]
            if temp == 0:
                S[i, j] = 0
            else:
                S[i, j] = 1 - 3 * min(B[i, j], R[i, j], G[i, j]) / temp

            num = 0.5 * (2 * R[i, j] - B[i, j] - G[i, j])
            den = np.sqrt((R[i, j]-G[i, j])*(R[i, j]-G[i, j])+(R[i, j]-B[i, j])*(G[i, j]-B[i, j]))
            if den == 0:
                H[i, j] = 0
            else:
                temp = num / den
                # 由于数值问题 可能会出现 num - den > 0 的情况 比如 0.04866234 和 0.04866233 因此需要判断一下
                if num / den > 1:
                    temp = 1
                theta = float(np.arccos(temp))
                H[i, j] = theta if B[i, j] <= G[i, j] else (np.pi * 2 - theta)
                H[i, j] = H[i, j] / (np.pi * 2)
    img = np.zeros([row, col, 3])
    img[:, :, 0] = H
    img[:, :, 1] = S
    img[:, :, 2] = I
    return np.array(img * 255, dtype=np.uint8)


def HSI2RGB(image):
    H, S, I = cv2.split(image)
    H = H / 255.
    S = S / 255.
    I = I / 255.
    row, col = H.shape
    img = np.zeros((row, col, 3))
    R, G, B = H.copy(), S.copy(), I.copy()
    for i in range(row):
        h = H[i] * 2 * np.pi
        # H大于等于0小于120度时
        a1 = h >= 0
        a2 = h < 2 * np.pi / 3
        a = a1 & a2  # 第一种情况的花式索引
        tmp = np.cos(np.pi / 3 - h)
        b = I[i] * (1 - S[i])
        r = I[i] * (1 + S[i] * np.cos(h) / tmp)
        g = 3 * I[i] - r - b
        B[i][a] = b[a]
        R[i][a] = r[a]
        G[i][a] = g[a]
        # H大于等于120度小于240度
        a1 = h >= 2 * np.pi / 3
        a2 = h < 4 * np.pi / 3
        a = a1 & a2  # 第二种情况的花式索引
        tmp = np.cos(np.pi - h)
        r = I[i] * (1 - S[i])
        g = I[i] * (1 + S[i] * np.cos(h - 2 * np.pi / 3) / tmp)
        b = 3 * I[i] - r - g
        R[i][a] = r[a]
        G[i][a] = g[a]
        B[i][a] = b[a]
        # H大于等于240度小于360度
        a1 = h >= 4 * np.pi / 3
        a2 = h < 2 * np.pi
        a = a1 & a2  # 第三种情况的花式索引
        tmp = np.cos(5 * np.pi / 3 - h)
        g = I[i] * (1 - S[i])
        b = I[i] * (1 + S[i] * np.cos(h - 4 * np.pi / 3) / tmp)
        r = 3 * I[i] - g - b
        B[i][a] = b[a]
        G[i][a] = g[a]
        R[i][a] = r[a]
    img[:, :, 0] = B
    img[:, :, 1] = G
    img[:, :, 2] = R
    return np.array(img * 255, dtype=np.uint8)


def main():
    img = cv2.imread("C:/Users/kwong/Pictures/boy.jpg", cv2.IMREAD_COLOR)
    # img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    HSI = RGB2HSI(img)
    # HSI = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    # img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    # img = cv2.cvtColor(HSI, cv2.COLOR_HSV2BGR)
    img = HSI2RGB(HSI)
    # img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    cv2.imshow("RGB", img)
    cv2.imshow("HSI", HSI)
    cv2.waitKey(0)
    pass


if __name__ == "__main__":
    main()