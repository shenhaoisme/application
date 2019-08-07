#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus.h>
 
int main() {
    DBusConnection *connection = NULL;
    DBusError error;
    char buffer[1024];
 
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "%s", error.message);
        abort();
    }
 // 当应用程序连接到总线时，它们会收到一个由总线提供的唯一名称
    puts("This is my unique name");
    puts(dbus_bus_get_unique_name(connection));
    fgets(buffer, sizeof(buffer), stdin);
     
    return 0;
}
// 现在你应该安装d-feet，这是Gnome项目中的DBUS调试器，然后启动它。 
// 将其指向session bus ，并在左侧面板中搜索程序输出给出的连接唯一名称。 您将看到应用程序的PID和命令名称：
//这里确实找到了我的interface ，过一会儿会进行超时处理



