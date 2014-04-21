#!/usr/bin/env python
#encoding=utf-8
'''
'''
import Image, ImageDraw
import sys
import string
'''
Answer:5808
'''
def next_num(num):
    prev = num[0]
    next = ''
    j = 0

    for i in range(len(num)):
        if num[i] != prev:
            next += str(i - j)
            next += num[i - 1] 
            j = i
        prev = num[i]

    next += str(len(num) - j)
    next += num[-1]
    return next

#print next_num(sys.argv[1])

num = '1'
for i in range(30):
    num = next_num(num)

print len(num)
