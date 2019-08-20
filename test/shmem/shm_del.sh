set -x       

ipcs -m | awk '$5==1024 {print $2}' |
while read s
do
    ipcrm -m $s
done
