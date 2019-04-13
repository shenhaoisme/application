OBJ_PATH=.obj
OBJ = \
      ${OBJ_PATH}/a.o \
      ${OBJ_PATH}/b.o \
      ${OBJ_PATH}/main.o


all : $(OBJ)
	@echo compile
${OBJ_PATH}/%.o : %.c myh.h
	gcc -c -Iinclude %@ < $<




 
