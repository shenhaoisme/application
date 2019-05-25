SRC_PATH = ../../common/
SRC = $(SRC_PATH)/msgale_api.c \
	$(SRC_PATH)threadale_api.c \
	$(SRC_PATH)os_wrapper.h
INCLUDE = -I${SRC_PATH}
LIB = -lpthread


test:
	gcc $(SRC) mmi.c ${INCLUDE} ${LIB} -o mmi
	gcc $(SRC) adapt.c ${INCLUDE} ${LIB} -o adapt

