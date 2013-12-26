#!/usr/bin/python
#coding=utf-8
#azhe 2013.12.12
#公式汇总:
#离心力:f1 = m * v**2 / R
#引力: f2 = G*m*M / R**2
#如果保持圆周运动，必须保持f1 = f2, => v = sqrt(G*M/R)
#加速齿轮参数设置必须满足，v的调节倍数与R调节倍数的开方成正比
#
import pygame
from pygame.locals import *
import math

NAME = "Universal Gravitation"
AUTHOR = "azhe"
VERSION = "0.1"
background_image_file = 'star.jpg'
earth_image_file = 'earth.png'
sun_image_file = 'sun.png'
screen_size = (640, 480)
back_color = (255, 255, 255) #white
#速度, 调节倍数
V_SCALE = 150
#距离, 调节倍数
S_SCALE = 1.0 / V_SCALE**2
#日地距离
R = 1.5e11 * S_SCALE
#比例尺， 缩小版
SCALE = 200.0 / R

#引力常量
G = 6.67e-11 #N m**2 /(kg**2)
#地球
earth_s_x, earth_s_y = (320.0 * R) / 200, (440 * R) / 200
#earth_v = 3e4 #m/s
earth_v = 3e4 * V_SCALE #m/s
earth_v_angle = 0
earth_m = 5.98e24 #kg
#太阳
sun_s_x, sun_s_y = (320.0 * R) / 200, (240 * R) / 200 #地日距离1.5e11
sun_v = 0
sun_v_angle = 0
sun_m = 1.989e30

#角度转为弧度
def angle_to_radian(angle):
    return int(angle) * math.pi / 180
#弧度转角度
def radian_to_angle(radian):
    return radian * 180 / math.pi
def pr_error(msg):
    print 'Error: ' , msg

class Ball:
    '''
    构造函数，初始位移(左上角为原点 (0,0))，
    速度，速度的方向（顺时针角度）
    受力大小，及方向
    质量
    '''
    #依据比例尺缩放
    def scale_position(self):
        self.image_x = self.s_x * SCALE - self.rect.width / 2.0
        self.image_y = self.s_y * SCALE - self.rect.height / 2.0
        return self.image_x, self.image_y


    def __init__(self, s_x=0, s_y=0,  \
            v=0, v_angle=0,     \
            m=0, image_file = earth_image_file):
        self.s_x = s_x
        self.s_y = s_y
        self.v = v
        self.v_angle = v_angle
        self.m = m
        if self.m == 0:
            pr_error("m can't be 0")
            return
        #x,y速度分量
        self.v_x = self.v * math.cos(angle_to_radian(self.v_angle))
        self.v_y = self.v * math.sin(angle_to_radian(self.v_angle))
        self.image = pygame.image.load(image_file).convert_alpha()
        self.rect = self.image.get_rect()
        #转换为图上坐标
        self.image_pos = self.scale_position()
    #b相对于a的位置，b到a连线与x轴的夹角，逆时针
    def get_angle(self, b):
        if self.s_x == b.s_x and self.s_y == b.s_y:
            #两点重合
            return -1
        offset_x = b.s_x - self.s_x
        offset_y = b.s_y - self.s_y
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

        self.a_angle = angle
        return angle

    #当前ball与其他ball之间的引力
    def get_gravity(self, b):
        return G * self.m * b.m / ((self.s_x - b.s_x)**2 + (self.s_y - b.s_y)**2)
    #当前ball受到其他ball引力而产生的加速度
    def get_acce(self, b):
        return self.get_gravity(b) / self.m

    def update_position(self, b, t):
        #加速度
        self.a = self.get_acce(b)
        self.a_angle = self.get_angle(b)
        self.a_x = self.a * math.cos(angle_to_radian(self.a_angle))
        self.a_y = self.a * math.sin(angle_to_radian(self.a_angle))

        #位移 x,y
        self.s_x += self.v_x * t + (1.0 / 2 ) * self.a_x * t**2
        self.s_y += self.v_y * t + (1.0 / 2 ) * self.a_y * t**2
        #速度
        self.v_x += self.a_x * t
        self.v_y += self.a_y * t
        #转换为图上坐标
        self.image_pos = self.scale_position()

def main():
    pygame.init()
    pygame.display.set_caption(NAME+ " " + VERSION + " " + AUTHOR)
    screen = pygame.display.set_mode(screen_size)
    screen.fill(back_color)
    #加载图片
    background_image = pygame.image.load(background_image_file).convert()
    background_pos = (0, 0)
    #地球和太阳
    earth = Ball(earth_s_x, earth_s_y, \
            earth_v, earth_v_angle, \
            earth_m, earth_image_file)
    sun = Ball(sun_s_x, sun_s_y, \
            sun_v, sun_v_angle, \
            sun_m, sun_image_file)
    
    #定时器
    clock = pygame.time.Clock()
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                exit()
        #每次重新放置背景背景
        screen.blit(background_image, background_pos)

        #画出地球, 太阳
        screen.blit(earth.image, earth.image_pos)
        screen.blit(sun.image, sun.image_pos)
        #设置30FPS, 计算每FPS具体的时间ms, 转为s
        time_per_frame = clock.tick(30) / 1000.0
        #每帧都更新地球 太阳位置
        earth.update_position(sun, time_per_frame)
        #print 'earth: a_x: ', earth.a_x, 'a_y: ', earth.a_y, \
                #'v_x: ', earth.v_x, 'v_y', earth.v_y, \
                #'s_x: ', earth.s_x, 's_y: ', earth.s_y
        sun.update_position(earth, time_per_frame)
        #刷新
        pygame.display.update()

if __name__ == '__main__':
    main()
