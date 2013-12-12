#!/usr/bin/python
#coding=utf-8

import pygame, sys
import math
from pygame.locals import *

background_image_file = 'panzi.jpg'
ball_image_file = 'ball.png'
screen_size = (640, 480)
backColor = (255, 255, 255) #white
PI = 3.1415926
#比例尺100:1
SCALE = 50.0
#碰撞因子, 速度减小比例
COLLISION_FACTOR = 0.5
WIND_FACTOR = 0.02
#精度
PRECISION = 0.1


#角度转为弧度
def angleToRadian(angle):
    return angle * PI / 180

class Ball(object):
    #angle以x轴参照，顺时针
    #参数:速度，速度偏角，加速度，加速度偏角，小球图片
    def __init__(self, v = 0, v_angle = 0, 
            a = 9.8, a_angle = 90, 
            image_name = ball_image_file):
        #小球的图片
        self.image = pygame.image.load(image_name).convert_alpha()
        self.rect = self.image.get_rect()
        #初始化小球变量
        self.v, self.v_angle, self.a, self.a_angle = \
                v * 1.0, v_angle * 1.0, a * 1.0, a_angle * 1.0
        #x, y方向速度分量
        self.v_x = self.v * math.cos(angleToRadian(self.v_angle))
        self.v_y = self.v * math.sin(angleToRadian(self.v_angle))
        #x, y方向 加速度分量
        self.a_x = self.a * math.cos(angleToRadian(self.a_angle))
        self.a_y = self.a * math.sin(angleToRadian(self.a_angle))
        print '(a_x, a_y) = ', self.a_x, self.a_y
        #x,y位移
        self.s_x, self.s_y = 0, 0



def main():
    pygame.init()
    screen = pygame.display.set_mode(screen_size)
    screen.fill(backColor)
    #加载 背景和小球图片到变量
    background_image = pygame.image.load(background_image_file).convert()
    background_pos = (0, 0)
    #小球对象
    ball = Ball(v=10)
    
    #time clock
    clock = pygame.time.Clock()
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                exit()
        #设置30FPS, 计算每FPS具体的时间ms, 转为s
        time_per_frame = clock.tick(30) / 1000.0
        
        #计算小球x, y方向位移
        ball.s_x += ball.v_x * time_per_frame + \
                (1.0 / 2) * ball.a_x * time_per_frame ** 2
        ball.s_y += ball.v_y * time_per_frame + \
                (1.0 / 2) * ball.a_y * time_per_frame ** 2
        #计算小球瞬时x, y方向速度
        ball.v_x += ball.a_x * time_per_frame
        ball.v_x *= (1 - WIND_FACTOR)
        ball.v_y += ball.a_y * time_per_frame
        ball.v_y *= (1 - WIND_FACTOR)

        #放置背景
        screen.blit(background_image, background_pos)
        #依据比例尺SCALE,计算小球在图中相对位置
        ball_relative_x, ball_relative_y = ball.s_x * SCALE, ball.s_y * SCALE

        #速度小于某一精度则认为静止
        if math.fabs(ball.v_x) < PRECISION:
            ball.v_x = 0
        #print '(x,y)= ', ball.s_x, ball.s_y
        #发生碰撞，速度反向且减小
        #碰到右边墙壁,
        if ball_relative_x > screen_size[0] - ball.rect.width:
            #不能超过边界
            ball_relative_x = screen_size[0] - ball.rect.width
            ball.s_x = ball_relative_x / SCALE
            #速度反向且减小
            ball.v_x = -(ball.v_x * COLLISION_FACTOR)
        #碰到左边墙壁
        if ball_relative_x < 0:
            ball_relative_x = 0
            ball.s_x = ball_relative_x / SCALE
            ball.v_x = -(ball.v_x * COLLISION_FACTOR)
        #碰到下边墙壁
        if ball_relative_y > screen_size[1] - ball.rect.height:
            ball_relative_y = screen_size[1] - ball.rect.height
            ball.s_y = ball_relative_y / SCALE
            ball.v_y = -(ball.v_y * COLLISION_FACTOR)
            #速度小于某一精度则认为静止
            if math.fabs(ball.v_y) < PRECISION:
                ball.v_y = 0
                ball.a_y = 0
        #碰到上边墙壁
        if ball_relative_y < 0:
            ball_relative_y = 0
            ball.s_y = ball_relative_y / SCALE
            ball.v_y = -(ball.v_y * COLLISION_FACTOR)
        print '(x,y)= ', ball_relative_x, ball_relative_y,  \
                'y_height: ', screen_size[1] - ball_relative_y - ball.rect.height, \
            'ball.w h = ', ball.rect.width, ball.rect.height, \
            'v_x, v_y = ', ball.v_x, ball.v_y, \
            'time: ', time_per_frame


        #画出小球
        screen.blit(ball.image, (ball_relative_x, ball_relative_y))
        #刷新
        pygame.display.update()

if __name__ == '__main__':
    main()
