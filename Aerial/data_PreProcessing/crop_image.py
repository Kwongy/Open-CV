"""
author: Kwong
time: 2019/9/29 14:31

"""

import sys
import os
import cv2
import numpy as np
import math
img_size = 512


def crop_train_data(img_dir, dir_name):
    """
    directory structure
        -img_dir
            -img_1
            -img_2
            ...
            -img_n
    """
    mk_dir = os.path.join(os.path.dirname(img_dir), dir_name)
    if not os.path.exists(mk_dir):
        os.mkdir(mk_dir)
    for dirpath, dirnames, filenames in os.walk(img_dir, topdown=True):
        for index in range(len(filenames)):
            img_url = os.path.join(dirpath, filenames[index])
            img_name = filenames[index].split(".")[0]
            img = cv2.imread(img_url)
            width = img.shape[0]
            heigh = img.shape[1]
            len_width = math.ceil(width / img_size)
            len_heigh = math.ceil(heigh / img_size)
            cnt = 0
            print("Start to crop img - {0}".format(img_name))
            for x in range(len_width):
                for y in range(len_heigh):
                    w_begin = x * img_size
                    w_end = (x + 1) * img_size
                    h_begin = y * img_size
                    h_end = (y + 1) * img_size
                    if w_end >= width:
                        w_end = width
                        w_begin = w_end - img_size
                    if h_end >= heigh:
                        h_end = heigh
                        h_begin = h_end - img_size
                    image = img[w_begin:w_end, h_begin:h_end, :]
                    save_url = os.path.join(mk_dir, "{0}_{1}.tif".format(img_name, cnt))
                    cv2.imwrite(save_url, image)
                    cnt += 1
    pass


if __name__ == "__main__":
    img_url = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\images"
    label_url = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\gt"
    crop_train_data(img_url, "crop_img")
    crop_train_data(label_url, "crop_label")

