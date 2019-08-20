test:
	 gcc threadale_api.c msgale_api.c  app1.c config.h  -lpthread -o app1
	 gcc threadale_api.c msgale_api.c  app2.c config.h  -lpthread -o app2
semapgore:
	gcc client.c -o client
	gcc server.c -o server

thread_conn:
	g++ thread_conn.cpp thread_conn.h -lpthread -o thread_conn

clean:
	rm  -f app1 app2 client server thread_conn
