# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/11/21 11:15 
"""

import numpy as np
from numpy import linalg
import matplotlib.pyplot as plt
import math


def fourier_transform():
    t_len = math.pi * 4
    g_t = []
    t = np.linspace(0, t_len, 1000)
    for i in range(len(t)):
        temp = 2 * math.sin(t[i]) + math.sin(2 * t[i] + 3)
        g_t.append(temp)
    f_len = 2
    f = np.linspace(0, f_len, 1000)
    g_cos, g_sin, g_f = [], [], []
    for c_f in range(len(f)):
        sinsum = cossum = 0
        for c_t in range(len(t)):
            tempsin = g_t[c_t] * math.sin(f[c_f] * t[c_t] * (-2 * math.pi))
            tempcos = g_t[c_t] * math.cos(f[c_f] * t[c_t] * (-2 * math.pi))
            sinsum += tempsin
            cossum += tempcos
        g_f.append(math.sqrt((cossum / len(t)) ** 2 + (sinsum / len(t)) ** 2))
        g_sin.append(sinsum / len(t))
        g_cos.append(cossum / len(t))

    f_g = []

    # 傅里叶变换，频率进行积分

    for c_t in range(len(t)):
        sinsum = cossum = 0
        for c_f in range(len(f)):
            tempsin = g_sin[c_f] * math.sin(f[c_f] * t[c_t] * (-2 * math.pi))
            tempcos = g_cos[c_f] * math.cos(f[c_f] * t[c_t] * (-2 * math.pi))
            sinsum = sinsum + tempsin
            cossum = cossum + tempcos
        f_g.append(2 * f_len * t_len * sinsum / len(f) + 2 * f_len * t_len * cossum / len(f))
    plt.figure("傅里叶变换", figsize=(6, 6))
    plt.subplot(2, 2, 1)
    # 原函数g_t(t)
    plt.scatter(t, g_t, s=1, color='red')
    plt.title("Original Function g_t(t)")
    plt.subplot(2, 2, 2)
    # 傅里叶变换虚轴函数g_sin(f)
    plt.scatter(f, g_sin, s=1, color='red')
    plt.title("Fourier(sin) g_sin(f)")
    plt.subplot(2, 2, 3)
    # 傅里叶变换 复数模 函数g_f(f)
    plt.scatter(f, g_f, s=1, color='blue')
    plt.title("Fourier(module) g_f(f)")
    plt.subplot(2, 2, 4)
    # 逆傅里叶变换还原后的函数f_g(t)
    plt.scatter(t, f_g, s=1, color='red')
    plt.title("restore f_g(t)")
    plt.show()

fourier_transform()