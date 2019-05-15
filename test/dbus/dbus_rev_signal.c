#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus.h>
 /*
To receive a signal you have to tell the bus what signals you are interested in
 so they are sent to your application, then you read messages off the bus and 
 can check what type they are and what interfaces and signal names each signal represents.
 要接收信号，您必须告诉总线您感兴趣的信号，以便将它们发送到您的应用程序，
 然后您从总线上读取消息，并检查它们的类型以及每个信号代表的接口和信号名称。
 
 */
 
 
int receive() {
	int ret;
    DBusConnection *connection = NULL;
    DBusError error;
	DBusMessage* msg;
	DBusMessageIter args;
    char *sigvalue;
 
    dbus_error_init(&error);
	// connect to the bus
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "%s", error.message);
        abort();
    }
 
    puts("This is my unique name");
    puts(dbus_bus_get_unique_name(connection));
   
 //步骤2:给连接名分配一个well-known的名字作为Bus name，这个步骤不是必须的，
 //可以用if 0来注释着一段代码，我们可以用这个名字来检查，是否已经开启了这个应用的另外的进程。

	ret = dbus_bus_request_name(connection, "test.singal.dest",
							DBUS_NAME_FLAG_REPLACE_EXISTING,
							&error);
							
	if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER  != ret){
		exit(1);
	}
	if(dbus_error_is_set(&error)){
		fprintf(stderr, "Name Error (%s)\n", error.message);
		 dbus_error_free(&error);
	}
	// add a rule for which messages we want to see
	// 步骤3:通知D-Bus daemon，希望监听来行接口test.signal.Type的信号
	dbus_bus_add_match(connection, 
         "type='signal',interface='test.signal.Type'", 
         &error); // see signals from the given interface
	dbus_connection_flush(connection);
	if (dbus_error_is_set(&error)) { 
	  fprintf(stderr, "Match Error (%s)\n", error.message);
	  exit(1); 
	}
	/*    //步骤4:在循环中监听，每隔开1秒，就去试图自己的连接中获取这个信号。
	这里给出的是从连接中获取任何消息的方式，所以获取后去检查一下这个消息
	是否我们期望的信号，并获取内容。我们也可以通过这个方式来获取method call消息。

	*/
	while (1) {
 
		// non blocking read of the next available message
		dbus_connection_read_write(connection, 0);
		msg = dbus_connection_pop_message(connection);
	 
		// loop again if we haven't read a message
		if (NULL == msg) {
			sleep(1);
			continue;
		}
		if(dbus_message_is_signal(msg, "test.signal.Type","Test"))
		{
			//read the param
			if(! dbus_message_iter_init(msg, &args))
				fprintf(stderr, "message has no arguments\n");
			else if(DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
				fprintf(stderr, "it is not string\n");
			else{
				dbus_message_iter_get_basic(&args,&sigvalue);
				printf("Got Signal with value %s\n", sigvalue);
			}
				
		}
		// free the message
        dbus_message_unref(msg);		
		
	}
	//dbus_connection_close(connection);
    return 0;
}

int main()
{
	receive();
}
