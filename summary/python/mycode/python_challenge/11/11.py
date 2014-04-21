#!/usr/bin/env python
#encoding=utf-8

'''
Answer: evil
'''

import Image

img = Image.open('cave.jpg')

for x in xrange(img.size[0]):
    for y in xrange(img.size[1]):
        if (x+y)%2 == 1:
            #print img.getpixel((x,y))
            img.putpixel((x,y), 0)

img.save('cave2.jpg')

'''
img_odd_even = Image.new(img.mode, (img.size[0]/2, img.size[1]/2))
pix_odd_even = img_odd_even.load()

img_even_odd = Image.new(img.mode, (img.size[0]/2, img.size[1]/2))
pix_even_odd = img_even_odd.load()

img_odd_odd = Image.new(img.mode, (img.size[0]/2, img.size[1]/2))
pix_odd_odd = img_odd_odd.load()

img_even_even = Image.new(img.mode, (img.size[0]/2, img.size[1]/2))
pix_even_even = img_even_even.load()

for x in xrange(0, img.size[0]/2):
    for y in xrange(0, img.size[1]/2):
        pix_odd_even[x, y] = pix[2*x+1, 2*y]
        #print 2*x+1, 2*y

for x in xrange(0, img.size[0]/2):
    for y in xrange(0, img.size[1]/2):
        pix_even_odd[x, y] = pix[2*x, 2*y+1]

for x in xrange(0, img.size[0]/2):
    for y in xrange(0, img.size[1]/2):
        pix_odd_odd[x, y] = pix[2*x+1, 2*y+1]

for x in xrange(0, img.size[0]/2):
    for y in xrange(0, img.size[1]/2):
        pix_even_even[x, y] = pix[2*x, 2*y]


img_odd_even.save('cave_odd_even.jpg')
img_even_odd.save('cave_even_odd.jpg')
img_even_odd.save('cave_odd_odd.jpg')
img_even_odd.save('cave_even_even.jpg')
'''
