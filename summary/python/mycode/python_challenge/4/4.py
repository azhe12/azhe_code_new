#!/usr/bin/env python
#!encoding=utf-8
'''
URL: http://www.pythonchallenge.com/pc/def/linkedlist.php

Description:
    1.  点击图片, 发现第一个nothing num = '12345'
    2.  不断的urlopen， 去找到下一个nothing num. 直到停止. 停止时(n=85, nothing=16044)
    3.  根据网页提示，下个nothing为 16044/2=8022, 继续从第一步骤开始, 第一个nothing num='8022'

answer:
    peak.html
'''
import re
import urllib2

TOP_URL = 'http://www.pythonchallenge.com/pc/def/linkedlist.php'
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:23.0) Gecko/20100101 Firefox/23.0'}

def get_nothing_num(url):
    #res = urllib2
    req = urllib2.Request(url, headers=headers)
    res = urllib2.urlopen(req).read()
    pat = '.*\ ([0-9]+)'
    try:
        return re.search(pat, res).group(1)
    except:
        print res
        return None

#nothing_num = '12345'  #第一个num
nothing_num = '25357'   #第二个num

#url = TOP_URL + '?nothing=' + first_nothing_num
n = 0
while n < 500:
    n += 1
    url = TOP_URL + '?nothing=' + nothing_num
    nothing_num = get_nothing_num(url)
    if nothing_num != None:
        print 'n=%d, nothing=%s' % (n, nothing_num)
    else:
        print 'Can\'t get num from url'
        exit()

