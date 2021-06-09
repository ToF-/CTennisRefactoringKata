# Points to the root of CppUTest, relative to where this file is.
# Remember to tweak this if you move this file.
CPPUTEST_HOME = ../cpputest

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -I$(CPPUTEST_HOME)/include

# Flags passed to the C++ compiler.
CFLAGS += -g -Wall -Wextra

VERSION=1

LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest
unit : TennisTest.c TennisGame$(VERSION).c
	g++ $(CPPFLAGS) $(CFLAGS) -o unittests $(USER_DIR)/TennisTest.c $(USER_DIR)/TennisGame$(VERSION).c $(LD_LIBRARIES)
	./unittests

clean :
	rm unittests
	
