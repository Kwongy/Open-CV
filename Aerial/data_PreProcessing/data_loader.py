# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/10/1 16:53 
"""

import cv2
from torch.utils.data import Dataset
import numpy as np
import random


def loadTrainData(txt_url, agument=True):
    return Dataset(txt_url, agument)


def loadValData(txt_url):
    return Dataset(txt_url, agument=False)


class Dataset(Dataset):
    def __init__(self, txt_url, agument=False):
        self.imgs = []
        self.agument = agument
        self.size = 512
        self.scale = [0.6, 0.7, 0.8, 0.9, 1.0]
        with open(txt_url, "r") as f:
            for line in f:
                line = line.rstrip()
                string = line.split(" ")
                self.imgs.append((string[0], string[1]))

    def __len__(self):
        return len(self.imgs)

    def __getitem__(self, index):
        img_url, label_url = self.imgs[index]
        img = cv2.imread(img_url) / 255.
        label = cv2.imread(label_url, 2)
        label[label == 255] = 1
        label.astype(np.uint8)
        if self.agument:
            img, label = self.transform(img, label)
        return np.transpose(img, [2, 0, 1]), label

    def transform(self, img, label):
        # Multi-scale
        img, label = self.Multi_scale(img, label)
        # Flip
        if np.random.random() < 0.2:
            img, label = self.Flip(img, label)
        # Noise
        if np.random.random() < 0.2:
            img = self.Gaussian_noise(img)
        # Rotate
        if np.random.random() < 0.2:
            img, label = self.Rotate(img, label)
        # Blur
        if np.random.random() < 0.08:
            img = self.Blur(img)
        return img, label

    def Multi_scale(self, image, label):
        cnt = random.randint(0, len(self.scale) - 1)
        h = image.shape[0]
        w = image.shape[1]
        height = int(h * self.scale[cnt])
        width = int(w * self.scale[cnt])
        big_small = min(height, width)
        random_x = random.randint(0, h - big_small)
        random_y = random.randint(0, w - big_small)
        image = image[random_x:random_x + big_small, random_y : random_y + big_small, :]
        label = label[random_x:random_x + big_small, random_y : random_y + big_small]
        image = cv2.resize(image, (self.size, self.size), interpolation=cv2.INTER_NEAREST)
        label = cv2.resize(label, (self.size, self.size), interpolation=cv2.INTER_NEAREST)
        return image, label

    def Blur(self, image):
        return cv2.blur(image, (3, 3))

    def Flip(self, image, label):
        randn = int(np.random.random() + 0.5)
        return cv2.flip(image, randn), cv2.flip(label, randn)

    def Gaussian_noise(self, image):
        mean = 0
        var = 0.01
        noise = np.random.normal(mean, var, image.shape)
        return image + noise

    def Rotate(self, image, label):
        angle = random.randint(1, 3) * 90
        img_w = image.shape[0]
        img_h = image.shape[1]
        M_rotate = cv2.getRotationMatrix2D((img_w / 2, img_h / 2), angle, 1)
        image = cv2.warpAffine(image, M_rotate, (img_w, img_h))
        label = cv2.warpAffine(label, M_rotate, (img_w, img_h))
        return image, label


if __name__ == "__main__":
    url = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\train.txt"
    data = loadTrainData(url)
    # data = loadValData(url)
    from Aeriali.model.deeplabV3_plus import deeplab
    print(len(data))
    model = deeplab(2, pretrained=False)
    for i, index in enumerate(data):
        img = np.transpose(index[0], [1, 2, 0])
        label = index[1]
        label[label == 1] = 255
        print(model(img))
        # input()
        cv2.imshow("img", img)
        cv2.imshow("label", label)
        cv2.waitKey(0)