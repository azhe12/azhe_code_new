#!/bin/bash
$? = 1
for project in $@
do
	while [ @?!=0 ];do 
		git clone ssh://htccgit1.china.htc.com.tw:29418/$project.git
	done
done

