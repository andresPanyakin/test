## -*- Makefile -*-
##
## User: fat
## Time: Jul 6, 2007 4:45:09 PM
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = cc
BASICOPTS = -g -lrt
CFLAGS = $(BASICOPTS) -xCC -mt


# Define the target directories.
TARGETDIR_production_line=Sun-x86-Solaris


all: $(TARGETDIR_production_line)/production_line

## Target: production_line
OBJS_production_line =  \
	$(TARGETDIR_production_line)/production_line.o
USERLIBS_production_line = $(SYSLIBS_production_line) 
DEPLIBS_production_line =  
LDLIBS_production_line = $(USERLIBS_production_line)


# Link or archive
$(TARGETDIR_production_line)/production_line: $(TARGETDIR_production_line) $(OBJS_production_line) $(DEPLIBS_production_line)
	$(LINK.c) $(CFLAGS_production_line) $(CPPFLAGS_production_line) -o $@ $(OBJS_production_line) $(LDLIBS_production_line)


# Compile source files into .o files
$(TARGETDIR_production_line)/production_line.o: $(TARGETDIR_production_line) production_line.c
	$(COMPILE.c) $(CFLAGS_production_line) $(CPPFLAGS_production_line) -o $@ production_line.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_production_line)/production_line \
		$(TARGETDIR_production_line)/production_line.o
	rm -f -r $(TARGETDIR_production_line)


# Create the target directory (if needed)
$(TARGETDIR_production_line):
	mkdir -p $(TARGETDIR_production_line)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

