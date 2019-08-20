#qmake -o Makefile BT.pro, but I just use makefile 

#CC = /usr/bin/arm-linux-gnueabihf-gcc
#CXX = /usr/bin/arm-linux-gnueabihf-g++
CXX=/usr/bin/g++


#just copy from ALE
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = /misc/80x8ee_dev/80x8ee/toolchain.rcpl0031/sysroots/x86_64-wrlinuxsdk-linux/usr/bin/armv5te-wrs-linux-gnueabi/arm926ejs-wrswrap-linux-gnueabi-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = .obj/
OBJPATH = .obj
SUBOBJS = .subobj
OBJS	   = \
           $(OBJPATH)/cmd_reg.o     \
           $(OBJPATH)/id.o          \
	       $(OBJPATH)/os_wrapper.o 	\
	       $(OBJPATH)/shell.o 		\
	       $(OBJPATH)/shell_exec.o 	\
	       $(OBJPATH)/syslog.o      \
           $(OBJPATH)/mem_wrapper.o 


all: ${OBJS}
	touch $(SUBOBJS)
	echo $(OBJS) >> $(SUBOBJS)

clean:
	echo "Nothing here"

$(OBJPATH)/%.o:	 %.cpp %.h
	$(RM) $@
	$(CXX) -c $(CFLAGS) -I../include  $@   $<




