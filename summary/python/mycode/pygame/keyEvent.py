#!/usr/bin/python
#coding=utf-8
import pygame, sys
from pygame.locals import *

background_image_name = 'panzi.jpg'
screen_size = (640, 480)

pygame.init()
screen = pygame.display.set_mode(screen_size, 0, 32)
#screen.image = pygame.image.load(background_image_name).convert()
background = pygame.image.load(background_image_name).convert()
move_x, move_y = 0, 0
x, y = 0, 0

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            sys.exit()
        elif event.type == KEYDOWN:
            if event.key == K_LEFT:
                move_x -= 1
            if event.key == K_RIGHT:
                move_x += 1
            if event.key == K_UP:
                move_y -= 1
            if event.key == K_DOWN:
                move_y += 1
    x += move_x
    y += move_y
    move_x, move_y = 0, 0

    screen.fill((0, 0, 0))
    screen.blit(background, (x, y))
    pygame.display.update()
