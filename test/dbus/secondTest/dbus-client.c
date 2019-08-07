#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <dbus/dbus.h>


const char *const SERVER_BUS_NAME = "com.just4coding.dbus";
const char *const CLIENT_BUS_NAME = "com.just4coding.client";
const char *const OBJECT_PATH_NAME_YES = "/com/just4coding/dbus/yes";
const char *const OBJECT_PATH_NAME_NO = "/com/just4coding/dbus/no";
const char *const INTERFACE_NAME = "com.just4coding.dbus_demo";
const char *const METHOD_NAME = "hello";


DBusError dbus_error;
void print_dbus_error(char *str);
// 客户端程序分别向 /com/just4coding/dbus/yes 和 /com/just4coding/dbus/no 两个object发送了字符串”alice”并打印出响应。
int main(int argc, char **argv)
{
    DBusConnection *conn;
    char input[80];

    dbus_error_init(&dbus_error);

    assert(conn = dbus_bus_get(DBUS_BUS_SYSTEM, &dbus_error));

    if (dbus_error_is_set(&dbus_error)) {
        print_dbus_error("dbus_bus_get");
    }

    const char *objects[] = {OBJECT_PATH_NAME_YES, OBJECT_PATH_NAME_NO, NULL};
    int i = 0;

    for ( ; objects[i]; i++) {
        DBusMessage *request;
        assert((request = dbus_message_new_method_call(SERVER_BUS_NAME, objects[i], INTERFACE_NAME, METHOD_NAME)));

        DBusMessageIter iter;
        dbus_message_iter_init_append(request, &iter);
        snprintf(input, sizeof(input), "alice");

        char *ptr = input;
        assert(dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &ptr));

        DBusPendingCall *pending_return;
        assert(dbus_connection_send_with_reply (conn, request, &pending_return, -1));

        assert(pending_return);
        dbus_connection_flush(conn);
        dbus_message_unref(request);

        dbus_pending_call_block(pending_return);

        DBusMessage *reply;
        assert((reply = dbus_pending_call_steal_reply (pending_return)));
        dbus_pending_call_unref(pending_return);

        char *s;
        if (dbus_message_get_args(reply, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID)) {
            printf("Reply: %s\n", s);
        } else {
            fprintf (stderr, "Did not get arguments in reply\n");
            exit(1);
        }

        dbus_message_unref(reply);
    }

    return 0;
}


void print_dbus_error(char *str)
{
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free(&dbus_error);
}