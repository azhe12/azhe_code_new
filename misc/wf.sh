#!/bin/bash
#计算标准输入中单词出现的频率，并按频率从大到小排序，默认显示前10个高频单词
#n为输出显示的行数, 默认为10行
#用法: wf.sh [n]
n=$1
if [ -z $n ];then
	n=10
fi
tr -cs A-Za-z\' '\n'|tr A-Z a-z|sort|uniq -c|sort -k1,1nr -k2|head -n $n
