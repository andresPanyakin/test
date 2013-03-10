## -*- Makefile -*-
##
## User: fat
## Time: May 17, 2007 12:42:37 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_pi_serial=Sun-x86-Solaris
TARGETDIR_pi_parallel_barrier=Sun-x86-Solaris

all: $(TARGETDIR_pi_serial)/pi_serial $(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier

## Target: pi_serial
OBJS_pi_serial =  \
	$(TARGETDIR_pi_serial)/pi_serial.o
USERLIBS_pi_serial = $(SYSLIBS_pi_serial) 
DEPLIBS_pi_serial =  
LDLIBS_pi_serial = $(USERLIBS_pi_serial)


# Link or archive
$(TARGETDIR_pi_serial)/pi_serial: $(TARGETDIR_pi_serial) $(OBJS_pi_serial) $(DEPLIBS_pi_serial)
	$(LINK.c) $(CFLAGS_pi_serial) $(CPPFLAGS_pi_serial) -o $@ $(OBJS_pi_serial) $(LDLIBS_pi_serial)


# Compile source files into .o files
$(TARGETDIR_pi_serial)/pi_serial.o: $(TARGETDIR_pi_serial) pi_serial.c
	$(COMPILE.c) $(CFLAGS_pi_serial) $(CPPFLAGS_pi_serial) -o $@ pi_serial.c

## Target: pi_parallel_barrier
OBJS_pi_parallel_barrier =  \
	$(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier.o
USERLIBS_pi_parallel_barrier = $(SYSLIBS_pi_parallel_barrier) 
DEPLIBS_pi_parallel_barrier =  
LDLIBS_pi_parallel_barrier = $(USERLIBS_pi_parallel_barrier)


# Link or archive
$(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier: $(TARGETDIR_pi_parallel_barrier) $(OBJS_pi_parallel_barrier) $(DEPLIBS_pi_parallel_barrier)
	$(LINK.c) $(CFLAGS_pi_parallel_barrier) $(CPPFLAGS_pi_parallel_barrier) -o $@ $(OBJS_pi_parallel_barrier) $(LDLIBS_pi_parallel_barrier)


# Compile source files into .o files
$(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier.o: $(TARGETDIR_pi_parallel_barrier) pi_parallel_barrier.c
	$(COMPILE.c) $(CFLAGS_pi_parallel_barrier) $(CPPFLAGS_pi_parallel_barrier) -o $@ pi_parallel_barrier.c


#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier \
		$(TARGETDIR_pi_parallel_barrier)/pi_parallel_barrier.o
	rm -f -r $(TARGETDIR_pi_parallel_barrier)


# Create the target directory (if needed)
$(TARGETDIR_pi_parallel_barrier):
	mkdir -p $(TARGETDIR_pi_parallel_barrier)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

