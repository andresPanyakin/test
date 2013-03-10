## -*- Makefile -*-
##
## User: fat
## Time: May 20, 2007 12:34:51 AM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_msgqueue_sem=Sun-x86-Solaris
TARGETDIR_msgqueue_cond=Sun-x86-Solaris


all: $(TARGETDIR_msgqueue_sem)/msgqueue_sem $(TARGETDIR_msgqueue_cond)/msgqueue_cond

## Target: msgqueue_sem
OBJS_msgqueue_sem =  \
	$(TARGETDIR_msgqueue_sem)/test_sem.o \
	$(TARGETDIR_msgqueue_sem)/msgqueue_sem.o
USERLIBS_msgqueue_sem = $(SYSLIBS_msgqueue_sem) -lrt
DEPLIBS_msgqueue_sem =  
LDLIBS_msgqueue_sem = $(USERLIBS_msgqueue_sem)


# Link or archive
$(TARGETDIR_msgqueue_sem)/msgqueue_sem: $(TARGETDIR_msgqueue_sem) $(OBJS_msgqueue_sem) $(DEPLIBS_msgqueue_sem)
	$(LINK.c) $(CFLAGS_msgqueue_sem) $(CPPFLAGS_msgqueue_sem) -o $@ $(OBJS_msgqueue_sem) $(LDLIBS_msgqueue_sem)


# Compile source files into .o files
$(TARGETDIR_msgqueue_sem)/test_sem.o: $(TARGETDIR_msgqueue_sem) test.c msgqueue_sem.h
	$(COMPILE.c) $(CFLAGS_msgqueue_sem) $(CPPFLAGS_msgqueue_sem) -o $@ -DTEST_SEM test.c

$(TARGETDIR_msgqueue_sem)/msgqueue_sem.o: $(TARGETDIR_msgqueue_sem) msgqueue_sem.c msgqueue_sem.h
	$(COMPILE.c) $(CFLAGS_msgqueue_sem) $(CPPFLAGS_msgqueue_sem) -o $@ msgqueue_sem.c



## Target: msgqueue_cond
OBJS_msgqueue_cond =  \
	$(TARGETDIR_msgqueue_cond)/test_cond.o \
	$(TARGETDIR_msgqueue_cond)/msgqueue_cond.o
USERLIBS_msgqueue_cond = $(SYSLIBS_msgqueue_cond) 
DEPLIBS_msgqueue_cond =  
LDLIBS_msgqueue_cond = $(USERLIBS_msgqueue_cond)


# Link or archive
$(TARGETDIR_msgqueue_cond)/msgqueue_cond: $(TARGETDIR_msgqueue_cond) $(OBJS_msgqueue_cond) $(DEPLIBS_msgqueue_cond)
	$(LINK.c) $(CFLAGS_msgqueue_cond) $(CPPFLAGS_msgqueue_cond) -o $@ $(OBJS_msgqueue_cond) $(LDLIBS_msgqueue_cond)


# Compile source files into .o files
$(TARGETDIR_msgqueue_cond)/test_cond.o: $(TARGETDIR_msgqueue_cond) test.c msgqueue_cond.h
	$(COMPILE.c) $(CFLAGS_msgqueue_cond) $(CPPFLAGS_msgqueue_cond) -o $@ -DTEST_COND test.c

$(TARGETDIR_msgqueue_cond)/msgqueue_cond.o: $(TARGETDIR_msgqueue_cond) msgqueue_cond.c msgqueue_cond.h
	$(COMPILE.c) $(CFLAGS_msgqueue_cond) $(CPPFLAGS_msgqueue_cond) -o $@ msgqueue_cond.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_msgqueue_sem)/msgqueue_sem \
		$(TARGETDIR_msgqueue_sem)/test_sem.o \
		$(TARGETDIR_msgqueue_sem)/msgqueue_sem.o \
		$(TARGETDIR_msgqueue_cond)/msgqueue_cond \
		$(TARGETDIR_msgqueue_cond)/test_cond.o \
		$(TARGETDIR_msgqueue_cond)/msgqueue_cond.o
	rm -f -r $(TARGETDIR_msgqueue_cond)
	rm -f -r $(TARGETDIR_msgqueue_sem)


# Create the target directory (if needed)
$(TARGETDIR_msgqueue_cond):
	mkdir -p $(TARGETDIR_msgqueue_cond)
$(TARGETDIR_msgqueue_sem):
	mkdir -p $(TARGETDIR_msgqueue_sem)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

