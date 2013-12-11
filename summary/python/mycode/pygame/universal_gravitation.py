#!/usr/bin/python
#coding=utf-8
import pygame
from pygame.locals import *
import math

background_image_file = 'panzi.jpg'
ball_image_file = 'ball.png'
screen_size = (640, 480)
backColor = (255, 255, 255) #white
#比例尺， 缩小版
SCALE = 200.0 / 1.5e11
#earth
earth_m = 5.98e24 #kg
earth_v = 3e4 #m/s
earth_v_angle = 0
earth_s_x, earth_s_y = 320, 440

#角度转为弧度
def angle_to_radian(angle):
    return angle * math.pi / 180
#弧度转角度
def radian_to_angle(radian):
    return radian * 180 / math.pi
#b相对余a的位置，b到a连线与x轴的夹角，逆时针
def position_to_angle(a_position_x, a_position_y, b_position_x, b_position_y):
    print a_position_x, a_position_y, b_position_x, b_position_y
    #判断是否在象限分割线上
    #if a_position_x == b_position_x:
        #if a_position_y < b_position_y:
            #return 90
        #elif a_position_y > b_position_y:
            #return 270
        #else: #重合
            #return -1
    #if a_position_y == b_position_y:
        #if a_position_x < b_position_x:
            #return 0
        #elif a_position_x > b_position_x:
            #return 180
        #else:
            #return -1
       
    if a_position_x == b_position_x and a_position_y == b_position_y:
        #两点重合
        return -1
    offset_x = b_position_x - a_position_x
    offset_y = b_position_y - a_position_y
    offset_r = math.sqrt(offset_x**2 + offset_y**2)
    #角度
    radian = math.asin(math.fabs(offset_y / offset_r))
    angle = radian_to_angle(radian)

    #第一象限
    if offset_x >= 0 and offset_y >= 0:
        pass
    elif offset_x <= 0 and offset_y >= 0:#第二象限
        angle = 180 - angle
    elif offset_x <= 0 and offset_y <= 0:#第三象限
        angle = 180 + angle
    elif offset_x >= 0 and offset_y <= 0:#第四象限
        angle = 360 - angle

    return angle

def pr_error(msg):
    print 'Error: ' , msg

class Ball:
    '''
    构造函数，初始位移(左上角为原点 (0,0))，
    速度，速度的方向（顺时针角度）
    受力大小，及方向
    质量
    '''
    def __init__(s_x=0, s_y=0,  \
            v=0, v_angle=0,     \
            f=0, f_angle=0,     \
            m=0):
        #x,y速度分量
        self.v_x = self.v * math.cos(angle_to_radian(self.v_angle))
        self.v_y = self.v * math.sin(angle_to_radian(self.v_angle))
        if self.m == 0:
            pr_error("m can't be 0")
            return
        #加速度
        self.a = self.f / self.m
        self.a_angle = self.f_angle
        self.a_x = self.a * math.cos(angle_to_radian(self.a_angle))
        self.a_y = self.a * math.sin(angle_to_radian(self.a_angle))


print position_to_angle(0, 0, -1, -1)

