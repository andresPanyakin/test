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
TARGETDIR_pthread_create=Sun-x86-Solaris


all: $(TARGETDIR_pthread_create)/pthread_create

## Target: pthread_create
OBJS_pthread_create =  \
	$(TARGETDIR_pthread_create)/pthread_create.o


# Link or archive
$(TARGETDIR_pthread_create)/pthread_create: $(TARGETDIR_pthread_create) $(OBJS_pthread_create)
	$(LINK.c) $(CFLAGS_pthread_create) $(CPPFLAGS_pthread_create) -o $@ $(OBJS_pthread_create) $(LDLIBS_pthread_create)


# Compile source files into .o files
$(TARGETDIR_pthread_create)/pthread_create.o: $(TARGETDIR_pthread_create) pthread_create.c
	$(COMPILE.c) $(CFLAGS_pthread_create) $(CPPFLAGS_pthread_creade) -o $@ pthread_create.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_create)/pthread_create \
		$(TARGETDIR_pthread_create)/pthread_create.o
	rm -f -r $(TARGETDIR_pthread_create)


# Create the target directory (if needed)
$(TARGETDIR_pthread_create):
	mkdir -p $(TARGETDIR_pthread_create)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

