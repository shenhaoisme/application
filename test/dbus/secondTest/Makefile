
all:
	gcc -o dbus-server dbus-server.c `pkg-config --libs --cflags dbus-1`
	gcc -o dbus-client dbus-client.c `pkg-config --libs --cflags dbus-1`

example2: #I dot known what's meaning
	gcc -o example2 example2.c `pkg-config --libs --cflags dbus-1`
example1:
	gcc -o example1 -Wall example1.c `pkg-config --cflags dbus-1` `pkg-config --libs dbus-1` 

clean:
	rm -f dbus-server dbus-client
	rm -f example1 example2
