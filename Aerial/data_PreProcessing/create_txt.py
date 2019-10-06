"""
author: Kwong
time: 2019/10/1 14:23

"""
import sys
import os


def get_txt(txt_url, dir_url, name):
    with open(txt_url, "w") as f:
        for dirpath, dirnames, filenames in os.walk(dir_url, topdown=True):
            for i in range(len(filenames)):
                if not filenames[i].endswith('tif'):
                    continue
                img_path = os.path.join(dirpath, filenames[i])
                label_path = img_path.replace(name, "crop_label")
                line = img_path + " " + label_path + "\n"
                f.write(line)


if __name__ == "__main__":
    txt = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\train.txt"
    dir = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\crop_img"
    get_txt(txt, dir, "crop_img")