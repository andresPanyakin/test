## -*- Makefile -*-
##
## User: fat
## Time: Jul 18, 2007 3:52:26 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt 


# Define the target directories.
TARGETDIR_global_mutex=Sun-x86-Solaris
TARGETDIR_global_rwlock=Sun-x86-Solaris
TARGETDIR_local_rwlock=Sun-x86-Solaris
TARGETDIR_local_mutex=Sun-x86-Solaris


all: $(TARGETDIR_global_mutex)/global_mutex $(TARGETDIR_global_rwlock)/global_rwlock $(TARGETDIR_local_rwlock)/local_rwlock $(TARGETDIR_local_mutex)/local_mutex

## Target: global_mutex
OBJS_global_mutex =  \
	$(TARGETDIR_global_mutex)/global_mutex.o
USERLIBS_global_mutex = $(SYSLIBS_global_mutex) 
DEPLIBS_global_mutex =  
LDLIBS_global_mutex = $(USERLIBS_global_mutex)


# Link or archive
$(TARGETDIR_global_mutex)/global_mutex: $(TARGETDIR_global_mutex) $(OBJS_global_mutex) $(DEPLIBS_global_mutex)
	$(LINK.c) $(CFLAGS_global_mutex) $(CPPFLAGS_global_mutex) -o $@ $(OBJS_global_mutex) $(LDLIBS_global_mutex)


# Compile source files into .o files
$(TARGETDIR_global_mutex)/global_mutex.o: $(TARGETDIR_global_mutex) global_mutex.c
	$(COMPILE.c) $(CFLAGS_global_mutex) $(CPPFLAGS_global_mutex) -o $@ global_mutex.c



## Target: global_rwlock
OBJS_global_rwlock =  \
	$(TARGETDIR_global_rwlock)/global_rwlock.o
USERLIBS_global_rwlock = $(SYSLIBS_global_rwlock) 
DEPLIBS_global_rwlock =  
LDLIBS_global_rwlock = $(USERLIBS_global_rwlock)


# Link or archive
$(TARGETDIR_global_rwlock)/global_rwlock: $(TARGETDIR_global_rwlock) $(OBJS_global_rwlock) $(DEPLIBS_global_rwlock)
	$(LINK.c) $(CFLAGS_global_rwlock) $(CPPFLAGS_global_rwlock) -o $@ $(OBJS_global_rwlock) $(LDLIBS_global_rwlock)


# Compile source files into .o files
$(TARGETDIR_global_rwlock)/global_rwlock.o: $(TARGETDIR_global_rwlock) global_rwlock.c
	$(COMPILE.c) $(CFLAGS_global_rwlock) $(CPPFLAGS_global_rwlock) -o $@ global_rwlock.c



## Target: local_rwlock
OBJS_local_rwlock =  \
	$(TARGETDIR_local_rwlock)/local_rwlock.o
USERLIBS_local_rwlock = $(SYSLIBS_local_rwlock) 
DEPLIBS_local_rwlock =  
LDLIBS_local_rwlock = $(USERLIBS_local_rwlock)


# Link or archive
$(TARGETDIR_local_rwlock)/local_rwlock: $(TARGETDIR_local_rwlock) $(OBJS_local_rwlock) $(DEPLIBS_local_rwlock)
	$(LINK.c) $(CFLAGS_local_rwlock) $(CPPFLAGS_local_rwlock) -o $@ $(OBJS_local_rwlock) $(LDLIBS_local_rwlock)


# Compile source files into .o files
$(TARGETDIR_local_rwlock)/local_rwlock.o: $(TARGETDIR_local_rwlock) local_rwlock.c
	$(COMPILE.c) $(CFLAGS_local_rwlock) $(CPPFLAGS_local_rwlock) -o $@ local_rwlock.c



## Target: local_mutex
OBJS_local_mutex =  \
	$(TARGETDIR_local_mutex)/local_mutex.o
USERLIBS_local_mutex = $(SYSLIBS_local_mutex) 
DEPLIBS_local_mutex =  
LDLIBS_local_mutex = $(USERLIBS_local_mutex)


# Link or archive
$(TARGETDIR_local_mutex)/local_mutex: $(TARGETDIR_local_mutex) $(OBJS_local_mutex) $(DEPLIBS_local_mutex)
	$(LINK.c) $(CFLAGS_local_mutex) $(CPPFLAGS_local_mutex) -o $@ $(OBJS_local_mutex) $(LDLIBS_local_mutex)


# Compile source files into .o files
$(TARGETDIR_local_mutex)/local_mutex.o: $(TARGETDIR_local_mutex) local_mutex.c
	$(COMPILE.c) $(CFLAGS_local_mutex) $(CPPFLAGS_local_mutex) -o $@ local_mutex.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_global_mutex)/global_mutex \
		$(TARGETDIR_global_mutex)/global_mutex.o \
		$(TARGETDIR_global_rwlock)/global_rwlock \
		$(TARGETDIR_global_rwlock)/global_rwlock.o \
		$(TARGETDIR_local_rwlock)/local_rwlock \
		$(TARGETDIR_local_rwlock)/local_rwlock.o \
		$(TARGETDIR_local_mutex)/local_mutex \
		$(TARGETDIR_local_mutex)/local_mutex.o
	rm -f -r $(TARGETDIR_global_rwlock)
	rm -f -r $(TARGETDIR_local_mutex)
	rm -f -r $(TARGETDIR_local_rwlock)
	rm -f -r $(TARGETDIR_global_mutex)


# Create the target directory (if needed)
$(TARGETDIR_global_rwlock):
	mkdir -p $(TARGETDIR_global_rwlock)
$(TARGETDIR_local_mutex):
	mkdir -p $(TARGETDIR_local_mutex)
$(TARGETDIR_local_rwlock):
	mkdir -p $(TARGETDIR_local_rwlock)
$(TARGETDIR_global_mutex):
	mkdir -p $(TARGETDIR_global_mutex)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

