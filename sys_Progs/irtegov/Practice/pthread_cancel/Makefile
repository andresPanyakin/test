## -*- Makefile -*-
##
## User: fat
## Time: Mar 12, 2007 1:35:29 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_pthread_cancel=Sun-x86-Solaris


all: $(TARGETDIR_pthread_cancel)/pthread_cancel

## Target: pthread_cancel
OBJS_pthread_cancel =  \
	$(TARGETDIR_pthread_cancel)/pthread_cancel.o


# Link or archive
$(TARGETDIR_pthread_cancel)/pthread_cancel: $(TARGETDIR_pthread_cancel) $(OBJS_pthread_cancel)
	$(LINK.c) $(CFLAGS_pthread_cancel) $(CPPFLAGS_pthread_cancel) -o $@ $(OBJS_pthread_cancel) $(LDLIBS_pthread_cancel)


# Compile source files into .o files
$(TARGETDIR_pthread_cancel)/pthread_cancel.o: $(TARGETDIR_pthread_cancel) pthread_cancel.c
	$(COMPILE.c) $(CFLAGS_pthread_cancel) $(CPPFLAGS_pthread_cancel) -o $@ pthread_cancel.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_cancel)/pthread_cancel \
		$(TARGETDIR_pthread_cancel)/pthread_cancel.o
	rm -f -r $(TARGETDIR_pthread_cancel)


# Create the target directory (if needed)
$(TARGETDIR_pthread_cancel):
	mkdir -p $(TARGETDIR_pthread_cancel)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

