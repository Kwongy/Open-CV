# _*_ coding: utf-8 _*_
"""
    Author: Kwong
    Create time: 2019/10/1 21:09 
"""

import argparse
import os
import time
import sys
import torch
from tensorboardX import SummaryWriter
import torch.nn as nn
from torch.autograd import Variable
from torch.utils import data
from Aeriali.model.deeplabV3_plus import deeplab
from Aeriali.data_PreProcessing.data_loader import loadValData, loadTrainData

sys.path.append("..")
os.environ["CUDA_VISIBLE_DEVICES"] = "0"
train_url = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\train.txt"
val_url = "F:\\PaperExperiment\\Aeriali\\dataset\\train\\val.txt"


def train(args):
    # setup logger
    cur_time = time.localtime()
    log_dir = './logs/' + "logs-{}-{}-{}-{}-{}".format(cur_time.tm_mon, cur_time.tm_mday,
                                                       cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec)
    # Setup Dataloader
    train_loader = loadTrainData(train_url)
    val_loader = loadValData(val_url)
    trainloader = data.DataLoader(train_loader, batch_size=args.batch_size, num_workers=0, shuffle=True)
    val_loader = data.DataLoader(val_loader, batch_size=len(val_loader), num_workers=0, shuffle=False)
    finetune = False
    freeze_bn = False
    # Setup Model
    weight_dir = ""
    if finetune:
        model = deeplab(2, pretrained=False)
        weight = torch.load(weight_dir)
        model.load_state_dict(weight, strict=False)
        if freeze_bn:
            for name, param in model.named_parameters():
                if 'bn' in name:
                    param.requires_grad = False
                    print('freeze layer: %s' % name)
    else:
        model = deeplab(2, pretrained=True)
    model.train()
    if torch.cuda.is_available():
        model = torch.nn.DataParallel(model, device_ids=range(torch.cuda.device_count()))
        model.float()
        model.cuda()
    # init class loss for semantic segmentation
    class_criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=args.l_rate, momentum=0.99, weight_decay=5e-4)
    writer = SummaryWriter(logdir=log_dir,
                           comment='fine tune on {}, lr {},{} epoch in total'.format(weight_dir, args.l_rate,
                                                                                     args.n_epoch))
    # freeze edge detection to do fine tune

    acc_min = 0
    for epoch in range(args.n_epoch):
        loss_sum = 0
        for i, (images, labels) in enumerate(trainloader):
            if torch.cuda.is_available():
                images = Variable(images).float().cuda()
                labels = Variable(labels).long().cuda()
            else:
                images = Variable(images).float()
                labels = Variable(labels).long()
            optimizer.zero_grad()
            predictions = model(images)
            loss = class_criterion(predictions, labels)
            loss.backward()
            writer.add_scalar('global loss', loss.item(), epoch * trainloader.__len__() + i)
            optimizer.step()
            loss_sum = loss_sum + loss.item()

        mean_loss = loss_sum / len(trainloader)
        print("Epoch [%d/%d] lr: %.7f mean_Loss: %.6f" % (
            epoch + 1, args.n_epoch, optimizer.state_dict()['param_groups'][0]['lr'], mean_loss))
        writer.add_scalar('mean loss', mean_loss, epoch)
        acc = 0
        cnt = 0
        with torch.no_grad():
            for i, (val_img, val_lab) in enumerate(val_loader):
                if torch.cuda.is_available():
                    val_img = Variable(val_img).float().cuda()
                else:
                    val_img = Variable(val_img).float()
                pred = model(val_img)
                pred = torch.argmax(pred.data, dim=1).cpu().numpy()
                for x in range(pred.shape[0]):
                    for y in range(pred.shape[1]):
                        for z in range(pred.shape[2]):
                            cnt += 1
                            if pred[x, y, z] == val_lab[x, y, z]:
                                acc += 1
        acc = acc / cnt
        if acc >= acc_min:
            acc_min = acc
            torch.save(model.module.state_dict(),
                       os.path.join(log_dir, "deeplab_{0}_{1}_{2}_{3}.pkl".format(cur_time.tm_mday,
                                                                                  cur_time.tm_hour, cur_time.tm_min,
                                                                                  cur_time.tm_sec)))
            print("loss : {0}, acc : {1}, Save model!".format(mean_loss, acc))
    torch.save(model.module.state_dict(), os.path.join(log_dir, "deeplab_{0}_{1}_{2}_{3}.pkl".format(cur_time.tm_mday,
                                                                                                     cur_time.tm_hour,
                                                                                                     cur_time.tm_min,
                                                                                                     cur_time.tm_sec)))
    # writer.export_scalars_to_json(os.path.join(log_dir, "./all_scalars.json"))
    writer.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Paremeters')
    parser.add_argument('--arch', nargs='?', type=str, default='Aeriali',
                        help='Deeplab')
    parser.add_argument('--n_epoch', nargs='?', type=int, default=200,
                        help='# of the epochs')
    parser.add_argument('--batch_size', nargs='?', type=int, default=2,
                        help='Batch Size')
    parser.add_argument('--l_rate', nargs='?', type=float, default=1e-3,
                        help='Learning Rate')
    args = parser.parse_args()
    train(args)
