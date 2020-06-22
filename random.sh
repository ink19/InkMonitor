#!/bin/sh
#
echo $(awk -v a=$(( (RANDOM % 1000) + 1 )) -v b=1000 'BEGIN{printf("%.2f",a/b)}')
 
