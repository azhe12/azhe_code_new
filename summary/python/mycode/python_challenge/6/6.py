#!/usr/bin/env python
#!encoding=utf-8

import re
import os
import zipfile
'''
提示，按照索引数字依次提取zipfile.getinfo().comment
'''

def get_nothing_num(file):
    with open(file, 'r') as f:
        lines = f.readlines()
        str = ''.join(lines)
    pat = '.*\ ([0-9]+)'
    try:
        return re.search(pat, str).group(1)
    except:
        print str
        return None

zip = zipfile.ZipFile('channel/channel.zip')
nothing_num = '90052'
path = os.path.join(os.getcwd(), 'channel')
n = 0
comments = ''
while nothing_num != None:
    n += 1
    file_name = '%s.txt' % nothing_num
    file = os.path.join(path, file_name)
    comments += zip.getinfo(file_name).comment
    #print file, n
    nothing_num = get_nothing_num(file)

print comments
'''
Step2:
'''

#comments = ''
#for info in zipfile.ZipFile('channel/channel.zip').infolist():
    #comments += info.comment

#print comments

