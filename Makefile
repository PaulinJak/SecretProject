# ---------------------------------------------------------------------
#      Local configuration
# ---------------------------------------------------------------------

# don't forget to run
# $ use diam
# $ usediam cplex
# in your shell before using this makefile.

## Cheated Makefile

## Putting OS related tag
UNAME := $(shell uname)

ILOG_ROOT=/opt/ibm/ILOG/CPLEX_Studio126
ILOG_SYSTEM=x86-64_linux
ILOG_LIBFORMAT=static_pic


CPLEX_DIR            = $(ILOG_ROOT)/cplex
CONCERT_DIR          = $(ILOG_ROOT)/concert
CPLEX_LIB_DIR        = $(CPLEX_DIR)/lib/$(ILOG_SYSTEM)/$(ILOG_LIBFORMAT)
CONCERT_LIB_DIR      = $(CONCERT_DIR)/lib/$(ILOG_SYSTEM)/$(ILOG_LIBFORMAT)
CPLEX_INCLUDE_DIR    = $(CPLEX_DIR)/include
CONCERT_INCLUDE_DIR  = $(CONCERT_DIR)/include


#  Add -DNDEBUG to those if you need it.

CPLEX_CXX_CFLAGS     = -I$(CPLEX_INCLUDE_DIR) -I$(CONCERT_INCLUDE_DIR) \
                       -m64 -fPIC -fno-strict-aliasing \
                       -fexceptions -O -DIL_STD

CPLEX_C_CFLAGS       = -I$(CPLEX_INCLUDE_DIR) \
                       -m64 -fPIC -fno-strict-aliasing 

CPLEX_CXX_LDDIRS     = -L$(CPLEX_LIB_DIR) -L$(CONCERT_LIB_DIR)
CPLEX_CXX_LDFLAGS    = -lconcert -lilocplex -lcplex -lm

ifeq ($(UNAME), Linux)
CPLEX_CXX_LDFLAGS += -pthread
endif

BOOST_FLAG=-I$(BOOST_DIR) 
BOOST_CXX_LDDIRS= -L$(BOOST_LIB_DIR)
# ---------------------------------------------------------------------


CXX_OBJ  := $(patsubst %.cpp, %.o, $(CXX_SRC))
OBJ      := $(CXX_OBJ) #$(C_OBJ) 


CCXX     := g++ -c #compile and assemble but do not link
CXXFLAGS += -Wall $(CPLEX_CXX_CFLAGS) $(BOOST_FLAG) -g -std=c++11 #-DNVERBOSE
LDFLAGS  += $(CPLEX_CXX_LDFLAGS) -g


LDFLAGS =
LDDIRS   += $(CPLEX_CXX_LDDIRS)
LINK     := g++

#$@ is the name of the file to be made.
#$? is the names of the changed dependents.
#$< the name of the related file that caused the action.
#$* the prefix shared by target and dependent files.


all : hashcode


hashcode: main.o fonctions.o carre.o
	$(LINK) $(LDDIRS) -o hashcode main.o fonctions.o carre.o $(LDFLAGS) -lm $(CXXFLAGS) 


main.o : src/main.cpp   src/fonctions.cpp src/matrix.hpp
	$(CCXX) $(LDDIRS) src/main.cpp -o main.o  $(LDFLAGS) -lm $(CXXFLAGS) 

fonctions.o : src/fonctions.cpp   
	$(CCXX) $(LDDIRS) src/fonctions.cpp -o fonctions.o  $(LDFLAGS) -lm $(CXXFLAGS) 

carre.o : src/carre.cpp   
	$(CCXX) $(LDDIRS) src/carre.cpp -o carre.o  $(LDFLAGS) -lm $(CXXFLAGS)


clean:
	rm -f *.o
