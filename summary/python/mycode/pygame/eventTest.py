#!/usr/bin/python
#coding=utf-8
import pygame
from pygame.locals import *
from sys import exit

pygame.init()
#screen
screen_size = (800, 600)
screen = pygame.display.set_mode(screen_size, 0)

background_color = (0, 0, 0)
screen.fill(background_color)
#pygame.display.flip()
#font
font = pygame.font.SysFont("arial", 16)
font_height = font.get_linesize()

event_text = []

while True:
    #获得event
    event = pygame.event.wait()
    event_text.append(str(event))
    #少于一屏的数据
    event_text = event_text[-screen_size[1] / font_height:]

    if event.type == QUIT:
        exit()

    x = 0
    y = 0
    #清空屏幕
    screen.fill(background_color)
    for text in event_text:
        #将event打印到screen上
        screen.blit(font.render(text, True, (0, 255, 0)), (x, y))
        y += font_height
    #刷新屏幕
    pygame.display.update()
