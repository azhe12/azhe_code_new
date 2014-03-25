#!/usr/bin/env python
import string

str = 'map'

charset = string.maketrans('','')[97:123]
set = set(charset)

str_new = ''
for c in str:
    if c in set:
        ord_c = ord(c) + 2
        if ord_c > ord('z'):
            ord_c = ord('a') + ord_c - ord('z') - 1

        c_new = chr(ord_c)
    else:
        c_new = c

    str_new += c_new

print 'Level 1 answer is: ' + str_new

