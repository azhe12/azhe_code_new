#!/usr/bin/env python
#encoding=utf-8
'''
Answer: 1756 mozart生日
'''

import datetime

for year in range(1996, 1582, -20):
    if datetime.date(year, 1, 1).weekday() == 3: #3 is Thursday
        print year

