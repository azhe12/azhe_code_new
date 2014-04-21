#!/usr/bin/env python
#encoding=utf-8
'''
URL:    http://www.pythonchallenge.com/pc/def/peak.html

Des:    
    1. 在源代码中得到banner.p
    2. 标题peak hell 发音类似与pickle
    3. 猜想banner.p中存储的是pickle序列化的python对象
    4. 使用pickle.load()加载并分析
    5. 打印得到答案: channel

Answer: channel
'''

import pickle
import os


source_file = os.getcwd() + '/' + 'banner.p'#读出序列化的obj

obj = pickle.load(open(source_file, 'r'))

str = ''

for l1 in obj:
    for tuple in l1:
        str += tuple[0]*tuple[1]
    str += '\n'

print str
