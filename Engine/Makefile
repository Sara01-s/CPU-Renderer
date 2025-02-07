# $(1) : Compiler					(gcc, g++)
# $(2) : Object file to generate	(*.o)
# $(3) : Source file 				(*.c, *.cpp)
# $(4) : Dependencies				(*.h, *.hpp)
# $(5) : Compiler flags				(-Wall, -pedantic)
 
define COMPILE
$(2) : $(3) $(4)
	$(1) -c $(3) -o $(2) $(5)
endef

# $(1) : Source file
# C or C++ File to Object file modus operandi e.g.
# input  : src/tinyPTC/xbcde.cpp
# output : obj/tinyPTC/xbcde.o

define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef


# $(1) : Dependency
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef


APP 	:= game
CFLAGS  := -Wall -Wpedantic #-Wsign-conversion
CCFLAGS := $(CFLAGS) -std=c++17
C       := gcc
CC      := g++
MKDIR   := mkdir -p
RM		:= rm
SRC     := src
OBJ     := obj
LIBS    := libs/picoPNG/libPicoPNG.a libs/tinyPTC/libTinyPTC.a
LIBSDIR := libs
INCDIRS := -I$(SRC) -I$(LIBSDIR)

# Activar optimizaciones si game es una release (uso: make RELEASE=1) 
# Activate optimizations if game is a release (usage: make RELEASE=1)
ifdef RELEASE 			
	CCFLAGS += -O1
else
	CCFLAGS += -g
endif

# % = * (anything)
ALLCPPS    := $(shell     find src/ -iname *.cpp)
ALLCS      := $(shell 	  find src/ -iname *.c)
ALLOBJ     := $(foreach   F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS    := $(shell 	  find src -type d)
OBJSUBDIRS := $(patsubst  $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: info libs libs-clean libs-cleanall

# APP Depende de los subdirectorios de obj y src/main.cpp
# App Depends on the subdirectories of obj and src/main.cpp
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
# Linkear
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS)


# $@ = %.0 (producto esperado) (target)
# $^ = %.c (dependencia) (dependency)

# foreach var "F" = "file in ..."
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))


# foreach rules e.g.
#$(OBJ)/%.o : $(SRC)/%.c
#	$(C) -o $(patsubst $(SRC)%, $(OBJ)%, $@) -c $^ $(CFLAGS)
#
#$(OBJ)/%.o : $(SRC)/%.cpp
#	$(CC) -o $(patsubst $(SRC)%, $(OBJ)%, $@) -c $^ $(CCFLAGS)


info: 
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))
	

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

# clean		: elimina *.o (deletes all and executable)
# cleanall	: eliminar *.o pero NO el ejecutable (deletes all but executable)


## CLEAN RULES
clean:
	$(RM) -r "./$(OBJ)"

clean-all: clean
	$(RM) "./$(APP)"

## LIB RULES
libs:
	$(MAKE) -C $(LIBDIR)

libs-clean:
	$(MAKE) -C $(LIBDIR) clean

libs-cleanall:
	$(MAKE) -C $(LIBDIR) cleanall

