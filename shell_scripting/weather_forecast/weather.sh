#!/bin/bash

URL=http://www.weather.com.cn/weather/101020100.shtml
wget $URL
WEATHER=weatherInfo.txt
SOURCE=${URL##*/}
TMP=tmp.$$
#grep "今天是" $SOURCE |sed -e 's/^.*今天是//'|awk '{ printf "%s %s %s ",$1,$2,$3 }'|sed 's///' #>> $TMP 
sed -n '/今天是/p' $SOURCE|sed -e 's/^.*今天是//'|tr -d '\r\n' >>$TMP
sed -n '/上海天气预报-今日/p' $SOURCE |awk '{printf " %s\t%s\n",$2,$3}' >>$TMP
cat $TMP|awk '{printf "%s %s %s %s %s %s\n",$1,$1,$2,$3,$4,$5}'|sed -e 's/年//' -e 's/月//' -e 's/日//' |tee $WEATHER
rm $TMP $SOURCE
