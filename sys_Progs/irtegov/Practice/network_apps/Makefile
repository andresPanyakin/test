## -*- Makefile -*-
##
## User: fat
## Time: May 20, 2007 6:01:07 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# Define the target directories.
TARGETDIR_forwarder=Sun-x86-Solaris


all: $(TARGETDIR_forwarder)/forwarder

## Target: forwarder
OBJS_forwarder =  \
	$(TARGETDIR_forwarder)/forwarder.o
SYSLIBS_forwarder = -lsocket -lnsl 
USERLIBS_forwarder = $(SYSLIBS_forwarder) 
DEPLIBS_forwarder =  
LDLIBS_forwarder = $(USERLIBS_forwarder)


# Link or archive
$(TARGETDIR_forwarder)/forwarder: $(TARGETDIR_forwarder) $(OBJS_forwarder) $(DEPLIBS_forwarder)
	$(LINK.c) $(CFLAGS_forwarder) $(CPPFLAGS_forwarder) -o $@ $(OBJS_forwarder) $(LDLIBS_forwarder)


# Compile source files into .o files
$(TARGETDIR_forwarder)/forwarder.o: $(TARGETDIR_forwarder) forwarder.c
	$(COMPILE.c) $(CFLAGS_forwarder) $(CPPFLAGS_forwarder) -o $@ forwarder.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_forwarder)/forwarder \
		$(TARGETDIR_forwarder)/forwarder.o
	rm -f -r $(TARGETDIR_forwarder)


# Create the target directory (if needed)
$(TARGETDIR_forwarder):
	mkdir -p $(TARGETDIR_forwarder)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

