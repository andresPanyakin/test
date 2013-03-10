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
CFLAGS = $(BASICOPTS) -xCC


# Define the target directories.
TARGETDIR_pthread_cancel_handler=Sun-x86-Solaris


all: $(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler

## Target: pthread_cancel_handler
OBJS_pthread_cancel_handler =  \
	$(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler.o


# Link or archive
$(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler: $(TARGETDIR_pthread_cancel_handler) $(OBJS_pthread_cancel_handler)
	$(LINK.c) $(CFLAGS_pthread_cancel_handler) $(CPPFLAGS_pthread_cancel_handler) -o $@ $(OBJS_pthread_cancel_handler) $(LDLIBS_pthread_cancel_handler)


# Compile source files into .o files
$(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler.o: $(TARGETDIR_pthread_cancel_handler) pthread_cancel_handler.c
	$(COMPILE.c) $(CFLAGS_pthread_cancel_handler) $(CPPFLAGS_pthread_cancel_handler) -o $@ pthread_cancel_handler.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler \
		$(TARGETDIR_pthread_cancel_handler)/pthread_cancel_handler.o
	rm -f -r $(TARGETDIR_pthread_cancel_handler)


# Create the target directory (if needed)
$(TARGETDIR_pthread_cancel_handler):
	mkdir -p $(TARGETDIR_pthread_cancel_handler)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

