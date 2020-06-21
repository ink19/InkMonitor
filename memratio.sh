#!/bin/bash



mem_total=`free | awk '/内存/ {print $2}'`

mem_used=`free | awk '/内存/ {print $3}'`

echo $(awk -v a=$mem_used -v b=$mem_total 'BEGIN{printf("%.2f",a/b)}')
