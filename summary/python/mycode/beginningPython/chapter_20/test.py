#!/usr/bin/python
#coding=utf-8
from util import *
import sys, re
class Handler:
    def callback(self, prefix, name, *args):
        method = getattr(self, prefix+name)
        if callable(method):
            return method(*args)
        else:
            return None

    def sub(self, name):
        def substitution(match):
            result = self.callback('sub_', name, match)
            if result:
                return result
            else:
                return match.group(0)

        return substitution

class HtmlRender(Handler):
    def sub_em(self, match):
        return '<em>%s</em>' %  match.group(1)

html_handler = HtmlRender()

print re.sub(r'\*(.*)\*', html_handler.sub('em'), '*azhe*')

#title = True
#print '<html><body>'
#for block in blocks(sys.stdin):
    #if title:
        #title = False
        #print '<h1>'
        #print block
        #print '</h1>'
    #else:
        #print '<p>'
        #print block
        #print '</p>'


#print '</html></body>'

