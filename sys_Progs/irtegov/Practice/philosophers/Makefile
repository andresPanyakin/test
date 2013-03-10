## -*- Makefile -*-
##
## User: fat
## Time: May 17, 2007 6:12:51 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_din_phil_ori=Sun-x86-Solaris
TARGETDIR_din_phil_ordered=Sun-x86-Solaris
TARGETDIR_din_phil_transaction=Sun-x86-Solaris


all: $(TARGETDIR_din_phil_ori)/din_phil_ori $(TARGETDIR_din_phil_ordered)/din_phil_ordered $(TARGETDIR_din_phil_transaction)/din_phil_transaction

## Target: din_phil_ori
OBJS_din_phil_ori =  \
	$(TARGETDIR_din_phil_ori)/din_phil_ori.o
USERLIBS_din_phil_ori = $(SYSLIBS_din_phil_ori) 
DEPLIBS_din_phil_ori =  
LDLIBS_din_phil_ori = $(USERLIBS_din_phil_ori)


# Link or archive
$(TARGETDIR_din_phil_ori)/din_phil_ori: $(TARGETDIR_din_phil_ori) $(OBJS_din_phil_ori) $(DEPLIBS_din_phil_ori)
	$(LINK.c) $(CFLAGS_din_phil_ori) $(CPPFLAGS_din_phil_ori) -o $@ $(OBJS_din_phil_ori) $(LDLIBS_din_phil_ori)


# Compile source files into .o files
$(TARGETDIR_din_phil_ori)/din_phil_ori.o: $(TARGETDIR_din_phil_ori) din_phil_ori.c
	$(COMPILE.c) $(CFLAGS_din_phil_ori) $(CPPFLAGS_din_phil_ori) -o $@ din_phil_ori.c



## Target: din_phil_ordered
OBJS_din_phil_ordered =  \
	$(TARGETDIR_din_phil_ordered)/din_phil_ordered.o
USERLIBS_din_phil_ordered = $(SYSLIBS_din_phil_ordered) 
DEPLIBS_din_phil_ordered =  
LDLIBS_din_phil_ordered = $(USERLIBS_din_phil_ordered)


# Link or archive
$(TARGETDIR_din_phil_ordered)/din_phil_ordered: $(TARGETDIR_din_phil_ordered) $(OBJS_din_phil_ordered) $(DEPLIBS_din_phil_ordered)
	$(LINK.c) $(CFLAGS_din_phil_ordered) $(CPPFLAGS_din_phil_ordered) -o $@ $(OBJS_din_phil_ordered) $(LDLIBS_din_phil_ordered)


# Compile source files into .o files
$(TARGETDIR_din_phil_ordered)/din_phil_ordered.o: $(TARGETDIR_din_phil_ordered) din_phil_ordered.c
	$(COMPILE.c) $(CFLAGS_din_phil_ordered) $(CPPFLAGS_din_phil_ordered) -o $@ din_phil_ordered.c



## Target: din_phil_transaction
OBJS_din_phil_transaction =  \
	$(TARGETDIR_din_phil_transaction)/din_phil_transaction.o
USERLIBS_din_phil_transaction = $(SYSLIBS_din_phil_transaction) 
DEPLIBS_din_phil_transaction =  
LDLIBS_din_phil_transaction = $(USERLIBS_din_phil_transaction)


# Link or archive
$(TARGETDIR_din_phil_transaction)/din_phil_transaction: $(TARGETDIR_din_phil_transaction) $(OBJS_din_phil_transaction) $(DEPLIBS_din_phil_transaction)
	$(LINK.c) $(CFLAGS_din_phil_transaction) $(CPPFLAGS_din_phil_transaction) -o $@ $(OBJS_din_phil_transaction) $(LDLIBS_din_phil_transaction)


# Compile source files into .o files
$(TARGETDIR_din_phil_transaction)/din_phil_transaction.o: $(TARGETDIR_din_phil_transaction) din_phil_transaction.c
	$(COMPILE.c) $(CFLAGS_din_phil_transaction) $(CPPFLAGS_din_phil_transaction) -o $@ din_phil_transaction.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_din_phil_ori)/din_phil_ori \
		$(TARGETDIR_din_phil_ori)/din_phil_ori.o \
		$(TARGETDIR_din_phil_ordered)/din_phil_ordered \
		$(TARGETDIR_din_phil_ordered)/din_phil_ordered.o \
		$(TARGETDIR_din_phil_transaction)/din_phil_transaction \
		$(TARGETDIR_din_phil_transaction)/din_phil_transaction.o
	rm -f -r $(TARGETDIR_din_phil_transaction)
	rm -f -r $(TARGETDIR_din_phil_ordered)
	rm -f -r $(TARGETDIR_din_phil_ori)


# Create the target directory (if needed)
$(TARGETDIR_din_phil_transaction):
	mkdir -p $(TARGETDIR_din_phil_transaction)
$(TARGETDIR_din_phil_ordered):
	mkdir -p $(TARGETDIR_din_phil_ordered)
$(TARGETDIR_din_phil_ori):
	mkdir -p $(TARGETDIR_din_phil_ori)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

