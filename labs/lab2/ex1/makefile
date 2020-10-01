CC = gcc
LD = gcc

CFLAGS = -fPIC -Wall -g

#the following is a SUFFIX RULE
%.o: %.c
	$(CC) $(CFLAGS) -c $<

#the following are MACROS
DYNLINKFLAGS = -g -shared -W1,-soname,$@.0
PROG_OBJS = hello.o
RM = rm -rf
PROG = hello
LIBS = -lc -L. 
LIB_FILES = libhello.so
LIB_MINOR = $(LIB_FILES).0.1
LIB_RELEASE = $(LIB_MINOR).0
LIB_OBJS = libhello.o

#the following is a TARGET
all: $(LIB_FILES) $(PROG)

#create the library with this RULE:
libhello.so: libhello.o
	$(LD) $(DYNLINKFLAGS) -o $(LIB_RELEASE) $< -lc
	ln -sf $(LIB_RELEASE) $(LIB_MINOR)
	ln -sf $(LIB_MINOR) $@
	ln -sf $@ $@.0

#create the program with this RULE:
$(PROG) : $(PROG_OBJS)
	$(LD) $(LDFLAGS) $(PROG_OBJS) $(LIBS) -o $(PROG)

#clean up the files with this RULE:
clean:
	$(RM) $(PROG_OBJS) $(PROG) $(LIB_OBJS) $(LIB_FILES) $(PROG_OBJS) $(LIB_RELEASE) $(LIB_MINOR) libhello.so.0

