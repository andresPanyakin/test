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
TARGETDIR_pthread_create_join=Sun-x86-Solaris


all: $(TARGETDIR_pthread_create_join)/pthread_create_join

## Target: pthread_create_join
OBJS_pthread_create_join =  \
	$(TARGETDIR_pthread_create_join)/pthread_create_join.o


# Link or archive
$(TARGETDIR_pthread_create_join)/pthread_create_join: $(TARGETDIR_pthread_create_join) $(OBJS_pthread_create_join)
	$(LINK.c) $(CFLAGS_pthread_create_join) $(CPPFLAGS_pthread_create_join) -o $@ $(OBJS_pthread_create_join) $(LDLIBS_pthread_create_join)


# Compile source files into .o files
$(TARGETDIR_pthread_create_join)/pthread_create_join.o: $(TARGETDIR_pthread_create_join) pthread_create_join.c
	$(COMPILE.c) $(CFLAGS_pthread_create_join) $(CPPFLAGS_pthread_creade) -o $@ pthread_create_join.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_create_join)/pthread_create_join \
		$(TARGETDIR_pthread_create_join)/pthread_create_join.o
	rm -f -r $(TARGETDIR_pthread_create_join)


# Create the target directory (if needed)
$(TARGETDIR_pthread_create_join):
	mkdir -p $(TARGETDIR_pthread_create_join)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

