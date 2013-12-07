#!/usr/bin/env python
# -*- coding: utf-8 -*-

#定义背景图像和鼠标图像名称
background_image_filename = "panzi.jpg"
sprite_image_filename = "ball.png"
screen_size = (640, 480)

import pygame
from pygame.locals import *
from sys import exit

#初始化pygame，为使用硬件做准备
pygame.init()

#创建一个窗口
screen = pygame.display.set_mode(screen_size, 0, 32)
#设置窗口标题
pygame.display.set_caption("Move")
#加载图片
background = pygame.image.load(background_image_filename).convert()
sprite = pygame.image.load(sprite_image_filename).convert_alpha()
#初始化移动的初始位置
x = 0
#定义一个时间对象
clock = pygame.time.Clock()
#定义运动速度(像素/秒)
speed = 100

while True:
  for event in pygame.event.get():
    #如果获得任意按键按下或者按退出键，则退出程序
    if event.type == KEYDOWN or event.type == QUIT:
      exit()
  #添加背景图像
  screen.blit(background, (0, 0))
  #添加移动图像
  screen.blit(sprite, (x, 100))
  #计算时间(ms)
  time_passed_s = clock.tick(30) / 1000.0
  print 'diff time: ', time_passed_s, " s"
  #计算移动距离(像素)
  distance_moved = speed * time_passed_s
  if x > 640:
    x = 0
  else:
    x += distance_moved
  #更新画面
  pygame.display.update()
