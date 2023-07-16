#
# Public domain, no copyright. Use at your own risk.
#

CC=gcc
CFLAGS+=-Wall -D_REENTRANT -DDEBUG -g -O0 -I$(INCLUDE_LOCATION) $(CPPFLAGS)
HELPER_LOCATION=../src
INCLUDE_LOCATION=../include
HELPER_LIBRARY=$(HELPER_LOCATION)/liborcania.so
LDFLAGS=-lc -lhelper $(shell pkg-config --libs check) -L$(HELPER_LOCATION)
VALGRIND_COMMAND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all
TARGET=helpers_test
VERBOSE=0
MEMCHECK=0

all: test

clean:
	rm -f *.o $(TARGET) *.log valgrind-*.txt

$(HELPER_LIBRARY): $(HELPER_LOCATION)/h_bin.c $(HELPER_LOCATION)/h_cpc.c $(HELPER_LOCATION)/h_lggr.c $(HELPER_LOCATION)/h_str.c $(HELPER_LOCATION)/h_memory.c $(HELPER_LOCATION)/h_memmgr.c
	cd $(HELPER_LOCATION) && $(MAKE) debug  $*

%: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: $(HELPER_LIBRARY) $(TARGET) helpers_test

check: test

test_%: % $(HELPER_LIBRARY)
	@if [ "$(VERBOSE)" = "0" ] && [ "$(MEMCHECK)" = "0" ]; then \
		LD_LIBRARY_PATH=$(HELPER_LOCATION):${LD_LIBRARY_PATH} ./run_test.sh ./$^; \
	elif [ "$(MEMCHECK)" = "0" ]; then \
		LD_LIBRARY_PATH=$(HELPER_LOCATION):${LD_LIBRARY_PATH} ./$^ ; \
	else \
		CK_FORK=no LD_LIBRARY_PATH=$(HELPER_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./$^ 2>valgrind-$@.txt; \
	fi
