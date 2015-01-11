#!/bin/bash
if [ ! -f $1 ];then
    echo "$1 not exist"
fi
mardown_file=$1
name=$(echo $mardown_file| sed 's/\.md//')
html_file=${name}.html
cat $mardown_file|markdown >$html_file
google-chrome $html_file &
