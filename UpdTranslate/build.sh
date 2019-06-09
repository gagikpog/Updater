#!/bin/sh
buildNum=`cat build`
echo $(($buildNum+1))>build
echo $buildNum

