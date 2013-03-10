## -*- Makefile -*-
##
## User: fat
## Time: May 17, 2007 2:07:38 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_producer_consumer=Sun-x86-Solaris
LDLIBS_producer_consumer=-lrt

all: $(TARGETDIR_producer_consumer)/p_c_funny $(TARGETDIR_producer_consumer)/p_c_condvar $(TARGETDIR_producer_consumer)/p_c_sem

## Target: p_c_funny
OBJS_p_c_funny =  \
	$(TARGETDIR_producer_consumer)/p_c_funny.o
OBJS_p_c_condvar =  \
	$(TARGETDIR_producer_consumer)/p_c_condvar.o
OBJS_p_c_sem =  \
	$(TARGETDIR_producer_consumer)/p_c_sem.o


# Link or archive
$(TARGETDIR_producer_consumer)/p_c_funny: $(TARGETDIR_producer_consumer) $(OBJS_p_c_funny)
	$(LINK.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ $(OBJS_p_c_funny) $(LDLIBS_producer_consumer)

$(TARGETDIR_producer_consumer)/p_c_condvar: $(TARGETDIR_producer_consumer) $(OBJS_p_c_condvar)
	$(LINK.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ $(OBJS_p_c_condvar) $(LDLIBS_producer_consumer)

$(TARGETDIR_producer_consumer)/p_c_sem: $(TARGETDIR_producer_consumer) $(OBJS_p_c_sem)
	$(LINK.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ $(OBJS_p_c_sem) $(LDLIBS_producer_consumer)

# Compile source files into .o files
$(TARGETDIR_producer_consumer)/p_c_funny.o: $(TARGETDIR_producer_consumer) p_c_funny.c
	$(COMPILE.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ p_c_funny.c

$(TARGETDIR_producer_consumer)/p_c_condvar.o: $(TARGETDIR_producer_consumer) p_c_condvar.c
	$(COMPILE.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ p_c_condvar.c

$(TARGETDIR_producer_consumer)/p_c_sem.o: $(TARGETDIR_producer_consumer) p_c_sem.c
	$(COMPILE.c) $(CFLAGS_producer_consumer) $(CPPFLAGS_producer_consumer) -o $@ p_c_sem.c


#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_producer_consumer)/p_c_funny \
		$(TARGETDIR_producer_consumer)/p_c_funny.o \
		$(TARGETDIR_producer_consumer)/p_c_condvar \
		$(TARGETDIR_producer_consumer)/p_c_condvar.o \
		$(TARGETDIR_producer_consumer)/p_c_sem \
		$(TARGETDIR_producer_consumer)/p_c_sem.o
	rm -f -r $(TARGETDIR_producer_consumer)


# Create the target directory (if needed)
$(TARGETDIR_producer_consumer):
	mkdir -p $(TARGETDIR_producer_consumer)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

