#gcc eg1.c -ldbus-1 -I/usr/local/include/dbus-1.0   -I/usr/include/dbus-1.0/ -I/usr/include/glib-2.0  -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include/ -I//usr/include/glib-2.0/glib


CC = gcc
CXX = g++
#CFLAGS = -Wno-psabi -fstack-protector-all -fno-omit-frame-pointer -g -march=armv5te -marm -mthumb-interwork -mtune=arm926ej-s -DLINUX=1 -DEGL_API_FB=1 -Wall -W -D_REENTRANT -fPIE $(DEFINES)
INCPATH =  -I/localdisk/work/platform/dbus-1.12.10/include/ -L/localdisk/work/platform/pkg-config-0.29.2/glib/glib/ -I/usr/include/glib-2.0

test:
	gcc -o dbus_connection_name -Wall dbus_conn_name.c `pkg-config --cflags dbus-1` `pkg-config --libs dbus-1`
send:
	gcc -o dbus_send_signal -Wall dbus_send_signal.c `pkg-config --cflags dbus-1` `pkg-config --libs dbus-1`

OBJS=eg1.o

all : 
  
