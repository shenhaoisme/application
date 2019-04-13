
include   ../makefile.pre

OBJS	   = \
           $(OBJPATH)/cmd_reg.o     \
           $(OBJPATH)/id.o          \
	       $(OBJPATH)/os_wrapper.o 	\
	       $(OBJPATH)/shell.o 		\
	       $(OBJPATH)/shell_exec.o 	\
	       $(OBJPATH)/syslog.o      \
           $(OBJPATH)/mem_wrapper.o 


all: $(OBJS)
	touch $(SUBOBJS)
	echo $(OBJS) >> $(SUBOBJS)

clean:
	echo "Nothing here"

$(OBJPATH)/%.o:	 %.cpp $(HEADERS)
	$(RM) $@
	$(CPP) $(CFLAGS) $(CLINK) $@ $(DPARAM) $(INCLUDE) $<

