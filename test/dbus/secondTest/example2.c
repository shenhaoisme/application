#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
 
static void check_and_abort(DBusError *error);
 
int main() {
    DBusConnection *connection = NULL;
    DBusError error;
    DBusMessage *msgQuery = NULL;
    DBusMessage *msgReply = NULL;
    const char *interfaceName = NULL;
    const char *versionValue = NULL;
 
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    check_and_abort(&error);
 
    interfaceName = "org.freedesktop.DBus";
 
    msgQuery = dbus_message_new_method_call(
        interfaceName,
        "/org/freedesktop/DBus",
        "org.freedesktop.DBus",
        "GetId");
 //创建消息时，函数dbus_connection_send_with_reply_and_block将在总线上发送消息并等待另一个应用程序的响应一秒钟（参数列表中的1000）
    msgReply = dbus_connection_send_with_reply_and_block(connection, msgQuery, 10000, &error);
    check_and_abort(&error);
    // 必须使用dbus_message_unref调用取消分配创建或返回的每条DBus消息
    dbus_message_unref(msgQuery);
 // 现在我们必须从回复消息中提取结果字符串，我们使用dbus_message_get_args来完成，这对于基本类型是可以的
    dbus_message_get_args(msgReply, &error, DBUS_TYPE_STRING, &versionValue, DBUS_TYPE_INVALID);
 
    printf("GetId: %s\n", versionValue);
     
    dbus_message_unref(msgReply);
     
    return 0;
}
 
static void check_and_abort(DBusError *error) {
    if (!dbus_error_is_set(error)) return;
    puts(error->message);
    abort();
}

// DBUS服务器应用程序有一个众所周知的名称（例如org.freedesktop.UPower）;

// sh@iZm5eavb11mttn4gjzqgm4Z:~/share/application/test/dbus/secondTest$ ./example2
// The name org.hao.shen was not provided by any .service files
// Aborted (core dumped)
// 从出错类型可以猜出，本意是找一个已经存在的server，和他已有的方法，然后直接去调用他。没成想
// 我这是阿里云，不能访问电池的电量。 没有这个方法，就用d-feet去查看org.freedesktop.DBus都有
// 什么方法，把请求方法换下就ok了