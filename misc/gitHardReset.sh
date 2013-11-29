#!/bin/bash
TOP="$(pwd)"
for dir in $@
do
	cd $TOP
	cd $dir
	git reset --hard HEAD^^
	git pull
done
