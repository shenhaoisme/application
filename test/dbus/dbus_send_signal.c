#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Connect to the DBUS bus and send a broadcast signal
 */
void sendsignal(char* sigvalue)
{
   DBusMessage* msg;
   DBusMessageIter args;
   DBusConnection* conn;
   DBusError err;
   int ret;
   dbus_uint32_t serial = 0;

   printf("Sending signal with value %s\n", sigvalue);

   // initialise the error value
   dbus_error_init(&err);

   // connect to the DBUS system bus, and check for errors
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Connection Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
      exit(1); 
   }

   // register our name on the bus, and check for errors
   ret = dbus_bus_request_name(conn, "test.signal.source", DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Name Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) { 
      exit(1);
   }

   // create a signal & check for errors 
   msg = dbus_message_new_signal("/test/signal/Object", // object name of the signal
                                 "test.signal.Type", // interface name of the signal
                                 "Test"); // name of the signal
   if (NULL == msg) 
   { 
      fprintf(stderr, "Message Null\n"); 
      exit(1); 
   }

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }

   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }
   dbus_connection_flush(conn);
   
   printf("Signal Sent\n");
   
   // free the message and close the connection
   dbus_message_unref(msg);
   dbus_connection_close(conn);
}

  
int send_a_signal( char * sigvalue)  
{  
    DBusError err;  
    DBusConnection * connection;  
    DBusMessage * msg;  
    DBusMessageIter arg;  
    dbus_uint32_t  serial =0;  
    int ret;  
  
    //步骤1:建立与D-Bus后台的连接  
      
    dbus_error_init(&err);  
       
    connection =dbus_bus_get(DBUS_BUS_SESSION ,&err );  
    if(dbus_error_is_set(&err)){  
        fprintf(stderr,"ConnectionErr : %s\n",err.message);  
        dbus_error_free(&err);  
    }  
    if(connection == NULL)  
        return -1;  
  
    //步骤2:给连接名分配一个well-known的名字作为Bus name，这个步骤不是必须的，可以用if 0来注释着一段代码，我们可以用这个名字来检查，是否已经开启了这个应用的另外的进程。  
#if 1  
    ret =dbus_bus_request_name(connection,"test.singal.source",DBUS_NAME_FLAG_REPLACE_EXISTING,&err);  
    if(dbus_error_is_set(&err)){  
        fprintf(stderr,"Name Err :%s\n",err.message);  
        dbus_error_free(&err);  
    }  
    if(ret !=DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)  
        return -1;  
#endif  
  
    //步骤3:发送一个信号  
    //根据图，我们给出这个信号的路径（即可以指向对象），接口，以及信号名，创建一个Message  
    if((msg =dbus_message_new_signal("/test/signal/Object","test.signal.Type","Test"))== NULL){  
        fprintf(stderr,"MessageNULL\n");  
        return -1;  
    }  
    //给这个信号（messge）具体的内容  
    dbus_message_iter_init_append(msg,&arg);  
   if(!dbus_message_iter_append_basic(&arg,DBUS_TYPE_STRING,&sigvalue)){  
        fprintf(stderr,"Out OfMemory!\n");  
        return -1;  
    }  
  
    //步骤4: 将信号从连接中发送  
    if( !dbus_connection_send(connection,msg,&serial)){  
        fprintf(stderr,"Out of Memory!\n");  
        return -1;  
    }  
    dbus_connection_flush(connection);  
    printf("Signal Send\n");  
  
   //步骤5: 释放相关的分配的内存。  
    dbus_message_unref(msg);  
    return 0;  
} 
int main( int argc , char ** argv){  
//   sendsignal("hell o world!");
   send_a_signal("Hello,world!");  
    return 0;  
}  
