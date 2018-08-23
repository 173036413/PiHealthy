#!/bin/bash
DATE=`date -u +"%Y-%m-%d__%H:%M:%S"`
HOSTNAME=`uname -n`
OS=`uname -o`
CORN=`uname -r`
TIME=`uptime -p | tr ' ' '_'`
AVER=`uptime | tr -s ' ' '\n' | tail -n 3 | xargs | tr ' ' ',' | tr -s ',' ' '
`
DISK=(`df -m | sort -n -k2 | tail -n1 | awk '{printf("%s %.2f", $2, $5)}'`)
MEM=(`free -m| tail -n +2 | head -n -1 | awk '{printf("%s %s %.2f", $2, $3, $3*100/$2)}'`)
WEN=`cat /sys/class/thermal/thermal_zone0/temp`
DISK_flag=normal
MEM_flag=normal
WEN_flag=normal
if [[ ${DISK[1]} > 90 ]]; then 
    DISK_flag=warning
elif [[ ${DISK[1]} > 80 ]]; then
    DISK_flag=note
fi
if [[ ${MEM[2]} > 90 ]]; then 
    MEM_flag=warning
elif [[ ${MEM[2]} > 80 ]]; then
    MEM_flag=note
fi
if [[ $WEN > 90000 ]]; then 
    WEN_flag=warning
elif [[ $WEN > 80000 ]]; then
    WEN_flag=note
fi
echo $DATE $HOSTNAME $OS $CORN $TIME $AVER ${DISK[0]} ${DISK[1]}% ${MEM[0]} ${MEM[2]}% $[$WEN / 1000] $DISK_flag $MEM_flag $WEN_flag
