import pygame,sys
pygame.init()
screen=pygame.display.set_caption('hello world!')
screen=pygame.display.set_mode([640,480])
screen.fill([255,255,255])
pygame.draw.circle(screen,[0,0,0],[150,200],10,1)
pygame.display.flip()
while True:
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit()
