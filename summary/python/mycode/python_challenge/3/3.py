#!/usr/bin/env python
#!encoding=utf-8
'''
在网页源码中找到型如'AAAaAAA'形式中的小写字母, 要求:
    1. EXACTLY 暗示，不能是'AAAAaAAA', 'AAAaAAAA'等超过3个大写字母的形式.
    2. file.readlines() 将file的所有lines读取并以list返回每行的列表
'''
import os
import re

cur_dir = os.getcwd()
source = cur_dir + '/' + '3.txt'
lines = []
with open(source, 'r+') as f:
    for line in f.readlines():
        lines.append(line)

f.close()

s = ''.join(lines)
#print s
pat = '[^A-Z][A-Z]{3}([a-z])[A-Z]{3}[^A-Z]'

print ''.join(re.findall(pat, s))
