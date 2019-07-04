#! /usr/bin/env/python
'''
测试进程间的队列通信
1 queue class是定义在 multiprocessing module里
2 job2应该加block的功能，和判断此时是否为空队列
'''
import multiprocessing as mp

#import thread as td
#modify parameters to queue
i=0
def job1(q):
	global i
	i+=1
	q.put(i)
	q.put("hello world")

def job2(q):
	#only get one value once
	print(q.get())
	print(q.get())
	
if __name__ == "__main__":
	q=mp.Queue()
	p1=mp.Process(target=job1,args=(q,))
	p2=mp.Process(target=job2,args=(q,))
	p1.start()
	p1.join()
	
	p2.start()
	p2.join()
