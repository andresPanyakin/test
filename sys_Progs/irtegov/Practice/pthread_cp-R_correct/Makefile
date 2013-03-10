## -*- Makefile -*-
##
## User: fat
## Time: Apr 3, 2007 3:52:06 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xc99=all -mt


# Define the target directories.
TARGETDIR_pthread_cp_r=Sun-x86-Solaris


all: $(TARGETDIR_pthread_cp_r)/pthread_cp_r

## Target: pthread_cp_r
OBJS_pthread_cp_r =  \
	$(TARGETDIR_pthread_cp_r)/pthread_cp_r.o


# Link or archive
$(TARGETDIR_pthread_cp_r)/pthread_cp_r: $(TARGETDIR_pthread_cp_r) $(OBJS_pthread_cp_r)
	$(LINK.c) $(CFLAGS_pthread_cp_r) $(CPPFLAGS_pthread_cp_r) -o $@ $(OBJS_pthread_cp_r) $(LDLIBS_pthread_cp_r)


# Compile source files into .o files
$(TARGETDIR_pthread_cp_r)/pthread_cp_r.o: $(TARGETDIR_pthread_cp_r) pthread_cp_r.c
	$(COMPILE.c) $(CFLAGS_pthread_cp_r) $(CPPFLAGS_pthread_cp_r) -o $@ pthread_cp_r.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_cp_r)/pthread_cp_r \
		$(TARGETDIR_pthread_cp_r)/pthread_cp_r.o
	rm -f -r $(TARGETDIR_pthread_cp_r)


# Create the target directory (if needed)
$(TARGETDIR_pthread_cp_r):
	mkdir -p $(TARGETDIR_pthread_cp_r)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

