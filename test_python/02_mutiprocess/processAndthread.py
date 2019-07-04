#! /usr/bin/env/python

import multiprocessing as mp
import threading as td
#import thread as td
def job(a,b):
    print("job")
	
if __name__ == "__main__":
    p1=mp.Process(target=job,args=(1,2))
	p2=mp.Process(target=job,args=(2,3))
    t1=td.Thread(target=job,args=(1,2))
    #t1=td.start_new_thread(job,(1,2))
    
    p1.start()
    p1.join()
	
	t1.start()
    t1.join()

