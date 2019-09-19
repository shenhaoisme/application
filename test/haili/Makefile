all:
	gcc socket_cli.c -o cli
	gcc socket_ser.c -o ser
v2:
	gcc threadAPI.c threadAPI.h socket_serV2.c -lpthread  -o serv2

clean:
	rm -f cli
	rm -f ser
