#!/usr/bin/env python
#encoding=utf-8

import urllib2
import random
import argparse

USER_AGENTS = ('Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:11.0) Gecko/20100101 Firefox/11.0',
               'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:22.0) Gecko/20100 101 Firefox/22.0',
               'Mozilla/5.0 (Windows NT 6.1; rv:11.0) Gecko/20100101 Firefox/11.0',
               'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.46 Safari/536.5',
               'Mozilla/5.0 (Windows; Windows NT 6.1) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.46 Safari/536.5',)

def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('url', type=str, help='url which you want fetch')
    parser.add_argument('-a', '--user_agent', action='store_true', help='use random user-agents')
    #parser.add_argument('-a', action='store_true', help='use random user-agents')
    parser.add_argument('-o', '--output_file', type=str, help='save html to outputfile')
    return parser

def fetch_url():
    parser = get_parser()
    args = parser.parse_args()
    #if sys.argc > 2:
        #parser.print_help()
    if not args.url:
        parser.print_help()

    #使用user_agent
    if args.user_agent:
        req = urllib2.Request(args.url, headers={'User-Agent':random.choice(USER_AGENTS)})
    else:
        req = urllib2.Request(args.url)

    #urllib2访问网页
    res = urllib2.urlopen(req).read()
    #将网页保存到文件
    if args.output_file:
        with open(args.output_file, 'w') as f:
            f.write(res)
    else:
        print res

    
if __name__ == '__main__':
    fetch_url()
