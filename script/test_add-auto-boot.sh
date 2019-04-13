#! /bin/sh

#using in raspberry
#put this file into /etc/init.d
#  
#    	   create a init link such as: ln -sf $this_file /etc/rc.d/sxxloop

OUTPUT_FILE=/root/output.txt
start(){
	
	echo `date` > ${OUTPUT_FILE}
	printf "start app !!!\n"

}

stop(){
	echo `date` > ${OUTPUT_FILE}
	printf "stop app !!!\n"
} 






### main logic ###
case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  status)
        status FOO
        ;;
  restart|reload|condrestart)
        stop
        start
        ;;
  *)
        echo $"Usage: $0 {start|stop|restart|reload|status}"
        exit 1
esac

exit 0