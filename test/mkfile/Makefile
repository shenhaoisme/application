OBJ_PATH=.obj
OBJ = ${OBJ_PATH}/a.o \
      ${OBJ_PATH}/b.o \
      main
	  
INCPATH = -I./include
all : ${OBJ}
	@echo compile
	
${OBJ_PATH}/a.o: 
	gcc -c ${INCPATH}  a.c -o ${OBJ_PATH}/a.o
${OBJ_PATH}/b.o: 
	gcc -c ${INCPATH}  b.c -o ${OBJ_PATH}/b.o
main: 
	gcc ${INCPATH}  ${OBJ_PATH}/a.o ${OBJ_PATH}/b.o  main.c -o  main 
	
clean:
	rm .obj/*.o
	rm main





 
