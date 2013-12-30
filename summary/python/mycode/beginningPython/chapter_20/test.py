#!/usr/bin/python
#coding=utf-8
from util import *
import sys
n = 0
for block in blocks(sys.stdin):
    print block
    print n, '\n'
    n += 1
