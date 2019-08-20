
so:
	gcc -fPIC -shared max.c max.h -o libmax.so

all:
	gcc main.c -L. -lmax -o main
clean:
	rm -f libmax.so main

