#! /bin/bash

MUSIC=/usr/share/scratch/Media/Sounds/Vocals/

if [ -f $MUSIC/Singer2.wav ];then
	aplay $MUSIC/Singer2.wav
else
	echo "no such file"
fi

Ya(){
	if [ -f $MUSIC/Ya.wav ];then
		aplay $MUSIC/Ya.wav
	else
		echo "no such file"
	fi
}
#main
for (( i=0; i<3; i++ ))
do
	Ya
	if [[ i -eq 1 ]];then
		sleep 1
	fi
done
