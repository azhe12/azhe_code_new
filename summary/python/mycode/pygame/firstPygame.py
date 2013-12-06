#!/usr/bin/python
#coding=utf-8

#图像名字
back_ground_image_name = 'panzi.jpg'
mouse_image_name = 'fish.png'

import pygame
#导入常用的函数和常量
from pygame.locals import *
from sys import exit

#init pygame
pygame.init()
#创建窗口, Surface
screen = pygame.display.set_mode((640, 480), 0, 32)
#窗口标题
pygame.display.set_caption("ahze's pygame")
#load and convert image to Surface
background = pygame.image.load(back_ground_image_name).convert()
mouse_cursor = pygame.image.load(mouse_image_name).convert_alpha()

while True:
    for event in pygame.event.get():
        #接受到退出事件后退出程序
        if event.type == QUIT:
            exit()
    
    #add background to screen, 将background surface放到screen surface的(0,0)位置
    screen.blit(background, (0, 0))
    #mouse position
    x,y = pygame.mouse.get_pos()
    x -= mouse_cursor.get_width() / 2
    y -= mouse_cursor.get_height() / 2
    #draw mouse cursor to screen
    screen.blit(mouse_cursor, (x, y))
    
    #refresh screen
    pygame.display.update()
