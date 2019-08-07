#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <dbus/dbus.h>

const char *const SERVER_BUS_NAME = "com.just4coding.dbus";
const char *const OBJECT_PATH_NAME_YES = "/com/just4coding/dbus/yes";
const char *const OBJECT_PATH_NAME_NO = "/com/just4coding/dbus/no";
const char *const INTERFACE_NAME = "com.just4coding.dbus_demo";
const char *const METHOD_NAME = "hello";

DBusError dbus_error;
void print_dbus_error(char *str);

int main(int argc, char **argv)
{
    DBusConnection *conn;
    int ret;

    dbus_error_init(&dbus_error);

    conn = dbus_bus_get(DBUS_BUS_SYSTEM, &dbus_error);

    if (dbus_error_is_set(&dbus_error)) {
        print_dbus_error("dbus_bus_get");
    }

    if (!conn) {
        exit(1);
    }

    ret = dbus_bus_request_name(conn, SERVER_BUS_NAME, DBUS_NAME_FLAG_DO_NOT_QUEUE, &dbus_error);

    if (dbus_error_is_set(&dbus_error)) {
        print_dbus_error("dbus_bus_request_name");
    }

    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        fprintf(stderr, "not primary owner, ret = %d\n", ret);
    }

    while (1) {
        if (!dbus_connection_read_write_dispatch(conn, -1)) {
            fprintf(stderr, "Not connected now.\n");
            exit (1);
        }

        DBusMessage *message;

        if ((message = dbus_connection_pop_message(conn)) == NULL) {
            fprintf(stderr, "Did not get message\n");
            continue;
        }

        if (dbus_message_is_method_call(message, INTERFACE_NAME, METHOD_NAME)) {
            char *s;
            if (dbus_message_get_args(message,
                                      &dbus_error,
                                      DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
            {
                printf("Received: %s\n", s);

                DBusMessage *reply;
                char answer[1024];

                assert(reply = dbus_message_new_method_return(message));

                DBusMessageIter iter;
                dbus_message_iter_init_append(reply, &iter);

                if (dbus_message_has_path(message, OBJECT_PATH_NAME_YES)) {
                    sprintf(answer, "Yes, %s", s);
                } else if (dbus_message_has_path(message, OBJECT_PATH_NAME_NO)) {
                    sprintf(answer, "No, %s", s);
                } else {
                    sprintf(answer, "No object found");
                }

                char *ptr = answer;
                assert(dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &ptr));

                assert(dbus_connection_send(conn, reply, NULL));
                dbus_connection_flush (conn);
                dbus_message_unref (reply);

            } else {
                print_dbus_error("Error getting message");
            }
        }
    }

    return 0;
}


void print_dbus_error(char *str)
{
    fprintf(stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free(&dbus_error);
}
