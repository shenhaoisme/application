test_msg:
	gcc thread_api.c msg_r_s_api.c app1.c  configs.h -lpthread -o app1
	gcc thread_api.c msg_r_s_api.c app2.c  configs.h -lpthread -o app2


test_thread:
	gcc -c thread_api.c configs.h -lpthread
	gcc -c  app1.c configs.h -lpthread
	gcc thread_api.o app1.o -o app1_main