## -*- Makefile -*-
##
## User: fat
## Time: May 25, 2007 1:30:44 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_httpclient_select=Sun-x86-Solaris
TARGETDIR_httpclient_pthread=Sun-x86-Solaris
TARGETDIR_httpclient_aio=Sun-x86-Solaris


all: $(TARGETDIR_httpclient_select)/httpclient_select $(TARGETDIR_httpclient_pthread)/httpclient_pthread $(TARGETDIR_httpclient_aio)/httpclient_aio

## Target: httpclient_select
OBJS_httpclient_select =  \
	$(TARGETDIR_httpclient_select)/httpclient_main.o \
	$(TARGETDIR_httpclient_select)/body_select.o
SYSLIBS_httpclient_select = -lsocket -lnsl 
USERLIBS_httpclient_select = $(SYSLIBS_httpclient_select) 
DEPLIBS_httpclient_select =  
LDLIBS_httpclient_select = $(USERLIBS_httpclient_select)


# Link or archive
$(TARGETDIR_httpclient_select)/httpclient_select: $(TARGETDIR_httpclient_select) $(OBJS_httpclient_select) $(DEPLIBS_httpclient_select)
	$(LINK.c) $(CFLAGS_httpclient_select) $(CPPFLAGS_httpclient_select) -o $@ $(OBJS_httpclient_select) $(LDLIBS_httpclient_select)


# Compile source files into .o files
$(TARGETDIR_httpclient_select)/httpclient_main.o: $(TARGETDIR_httpclient_select) httpclient_main.c
	$(COMPILE.c) $(CFLAGS_httpclient_select) $(CPPFLAGS_httpclient_select) -o $@ httpclient_main.c

$(TARGETDIR_httpclient_select)/body_select.o: $(TARGETDIR_httpclient_select) body_select.c
	$(COMPILE.c) $(CFLAGS_httpclient_select) $(CPPFLAGS_httpclient_select) -o $@ body_select.c



## Target: httpclient_pthread
OBJS_httpclient_pthread =  \
	$(TARGETDIR_httpclient_pthread)/httpclient_main.o \
	$(TARGETDIR_httpclient_pthread)/body_pthread.o
SYSLIBS_httpclient_pthread = -lsocket -lnsl
USERLIBS_httpclient_pthread = $(SYSLIBS_httpclient_pthread) 
DEPLIBS_httpclient_pthread =  
LDLIBS_httpclient_pthread = $(USERLIBS_httpclient_pthread)


# Link or archive
$(TARGETDIR_httpclient_pthread)/httpclient_pthread: $(TARGETDIR_httpclient_pthread) $(OBJS_httpclient_pthread) $(DEPLIBS_httpclient_pthread)
	$(LINK.c) $(CFLAGS_httpclient_pthread) $(CPPFLAGS_httpclient_pthread) -o $@ $(OBJS_httpclient_pthread) $(LDLIBS_httpclient_pthread)


# Compile source files into .o files
$(TARGETDIR_httpclient_pthread)/httpclient_main.o: $(TARGETDIR_httpclient_pthread) httpclient_main.c
	$(COMPILE.c) $(CFLAGS_httpclient_pthread) $(CPPFLAGS_httpclient_pthread) -o $@ httpclient_main.c

$(TARGETDIR_httpclient_pthread)/body_pthread.o: $(TARGETDIR_httpclient_pthread) body_pthread.c
	$(COMPILE.c) $(CFLAGS_httpclient_pthread) $(CPPFLAGS_httpclient_pthread) -o $@ body_pthread.c



## Target: httpclient_aio
OBJS_httpclient_aio =  \
	$(TARGETDIR_httpclient_aio)/httpclient_main.o \
	$(TARGETDIR_httpclient_aio)/body_aio.o
SYSLIBS_httpclient_aio = -lsocket -lnsl -lrt
USERLIBS_httpclient_aio = $(SYSLIBS_httpclient_aio) 
DEPLIBS_httpclient_aio =  
LDLIBS_httpclient_aio = $(USERLIBS_httpclient_aio)


# Link or archive
$(TARGETDIR_httpclient_aio)/httpclient_aio: $(TARGETDIR_httpclient_aio) $(OBJS_httpclient_aio) $(DEPLIBS_httpclient_aio)
	$(LINK.c) $(CFLAGS_httpclient_aio) $(CPPFLAGS_httpclient_aio) -o $@ $(OBJS_httpclient_aio) $(LDLIBS_httpclient_aio)


# Compile source files into .o files
$(TARGETDIR_httpclient_aio)/httpclient_main.o: $(TARGETDIR_httpclient_aio) httpclient_main.c
	$(COMPILE.c) $(CFLAGS_httpclient_aio) $(CPPFLAGS_httpclient_aio) -o $@ httpclient_main.c

$(TARGETDIR_httpclient_aio)/body_aio.o: $(TARGETDIR_httpclient_aio) body_aio.c
	$(COMPILE.c) $(CFLAGS_httpclient_aio) $(CPPFLAGS_httpclient_aio) -o $@ body_aio.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_httpclient_select)/httpclient_select \
		$(TARGETDIR_httpclient_select)/httpclient_main.o \
		$(TARGETDIR_httpclient_select)/body_select.o \
		$(TARGETDIR_httpclient_pthread)/httpclient_pthread \
		$(TARGETDIR_httpclient_pthread)/httpclient_main.o \
		$(TARGETDIR_httpclient_pthread)/body_pthread.o \
		$(TARGETDIR_httpclient_aio)/httpclient_aio \
		$(TARGETDIR_httpclient_aio)/httpclient_main.o \
		$(TARGETDIR_httpclient_aio)/body_aio.o
	rm -f -r $(TARGETDIR_httpclient_aio)
	rm -f -r $(TARGETDIR_httpclient_select)
	rm -f -r $(TARGETDIR_httpclient_pthread)


# Create the target directory (if needed)
$(TARGETDIR_httpclient_aio):
	mkdir -p $(TARGETDIR_httpclient_aio)
$(TARGETDIR_httpclient_select):
	mkdir -p $(TARGETDIR_httpclient_select)
$(TARGETDIR_httpclient_pthread):
	mkdir -p $(TARGETDIR_httpclient_pthread)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

