#!/bin/bash
TIME=`date -u +"%Y-%m-%d__%H:%M:%S"`
eval DISK=(`df -m| grep -v tmpfs | tail -n +2 |awk '{printf("%s %s %s\t%s\n",$6,$2,$4,$5)}' ALL=$2 REST=$4` NR=$ALL)
NUME=(`df -m| grep -v tmpfs | tail -n +2 |wc -l`)
ALL=0
REST=0
for i in `seq 1 $NUME`;do
    echo $TIME 1 ${DISK[$i-1+3*($i-1)]} ${DISK[$i+3*($i-1)]} ${DISK[$i+1+3*($i-1)]} ${DISK[$i+2+3*($i-1)]};
    ALL=$ALL+${DISK[$i+3*($i-1)]}
    REST=$REST+${DISK[$i+1+3*($i-1)]}
done  
#FINE=`echo $[$REST]/$[$ALL]`|bc 
#| awk {printf("%.0f",$1,$2)}`
echo $TIME 0 disk $[$ALL] $[$REST] $[$[$REST]*100/$[$ALL]]% 
