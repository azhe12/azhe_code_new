#!/usr/bin/env python
#encoding=utf-8

import urllib2,cookielib

python_challenge_url = 'http://www.pythonchallenge.com'
pc_17_url = python_challenge_url + '/pc/return/romance.html'
auth_handler = urllib2.HTTPBasicAuthHandler()
#auth_handler.add_password('inflate_azhe', python_challenge_url, 'huge', 'file')
auth_handler.add_password('inflate', python_challenge_url, 'huge', 'file')

jar = cookielib.CookieJar()
cookie_handler = urllib2.HTTPCookieProcessor(jar)

opener = urllib2.build_opener(auth_handler, cookie_handler)

opener.open(pc_17_url)

list(jar)
