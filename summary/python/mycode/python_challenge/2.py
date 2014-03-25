#!/usr/bin/env python
#!encoding=utf-8
'''
在URL源码中的的乱码中，提取英文字母
'''
import string
str = 'map'

charset = string.maketrans('','')[97:123]
set = set(charset)
lines = []
with open('2.txt', 'r+') as f:
    for line in f.readlines():
        lines.append(line)

file_str = ''.join(lines)


str_new = ''
for c in file_str:
    if c in set:
        str_new += c

print 'Level 2 answer is: ' +str_new

