#!/bin/bash 
DATE=`date -u +"%Y-%m-%d_%H:%M:%S"`
FI=$[`cat /proc/stat | head -n 1 | tr "a-z" "0" | tr " " "+"`]
ID1=$[`cat /proc/stat | head -n 1 | tr " " "\n"| head -n 6 | tail -n 1`]
sleep 0.5
LA=$[`cat /proc/stat | head -n 1 | tr "a-z" "0" | tr " " "+"`]
ID2=$[`cat /proc/stat | head -n 1 | tr " " "\n"| head -n 6 | tail -n 1`]
NOW=$[$LA-$FI]
ID=$[$ID2-$ID1]
#echo $ID $NOW
#pcpu=$[$[100*$[$NOW-$ID]]/$NOW]
Cpu=`echo "scale=2;(1-($ID/$NOW))*100"|bc`
WEN=`cat /sys/class/thermal/thermal_zone0/temp`
#echo $Cpu
load=(`uptime | awk '{printf("%s %s %s", $10, $11, $12)}'`)
flag=normal
if [[ $WEN > 70000 ]]; then
    flag=warning
elif [[ $WEN > 50000 ]]; then
    flag=note
fi
echo $DATE ${load[0]} ${load[1]} ${load[2]} $Cpu% $[$WEN / 1000] $flag 

