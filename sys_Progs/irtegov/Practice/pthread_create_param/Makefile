## -*- Makefile -*-
##
## User: Dmitry V Irtegov
## Time: Mar 9, 2007 11:49:08 AM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_pthread_create_param=Sun-x86-Solaris


all: $(TARGETDIR_pthread_create_param)/pthread_create_param

## Target: pthread_create_param
OBJS_pthread_create_param =  \
	$(TARGETDIR_pthread_create_param)/pthread_create_param.o


# Link or archive
$(TARGETDIR_pthread_create_param)/pthread_create_param: $(TARGETDIR_pthread_create_param) $(OBJS_pthread_create_param)
	$(LINK.c) $(CFLAGS_pthread_create_param) $(CPPFLAGS_pthread_create_param) -o $@ $(OBJS_pthread_create_param) $(LDLIBS_pthread_create_param)


# Compile source files into .o files
$(TARGETDIR_pthread_create_param)/pthread_create_param.o: $(TARGETDIR_pthread_create_param) pthread_create_param.c
	$(COMPILE.c) $(CFLAGS_pthread_create_param) $(CPPFLAGS_pthread_creade) -o $@ pthread_create_param.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_create_param)/pthread_create_param \
		$(TARGETDIR_pthread_create_param)/pthread_create_param.o
	rm -f -r $(TARGETDIR_pthread_create_param)


# Create the target directory (if needed)
$(TARGETDIR_pthread_create_param):
	mkdir -p $(TARGETDIR_pthread_create_param)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

