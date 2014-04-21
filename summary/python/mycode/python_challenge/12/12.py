#!/usr/bin/env python
#encoding=utf-8
'''
莫名其妙发现其中evil2.gfx是，5张图片的混合....
'''

types =  ['jpg','png','gif','png','jpg']
for i in range(5): open('evil2%d.%s' % (i, types[i]),'wb').write(str[i::5])
