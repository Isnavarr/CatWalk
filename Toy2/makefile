# Usage:
# change Home to point to the directory where all of your items are
# add this directory also to your LD_LIBRARY_PATH by running after you make
# export LD_LIBRARY_PATH=$HOME:$LD_LIBRARY_PATH

CC = g++

_OBJS = math.o print.o addDiff.o

CFLAGS += -Wall -Werror -fPIC

LIB = shared

SHARED_LIB = lib$(LIB).so

HOME = /home/jessicalam/Desktop/CatWalk/Toy2/

#LD_LIBRARY_PATH += $(HOME)

.PHONY: all

all: $(SHARED_LIB)
	$(CC) -L $(HOME) -Wall main.cpp -o main -l $(LIB)

$(SHARED_LIB): $(_OBJS)
	$(CC) -shared -o $(SHARED_LIB) $(_OBJS)

$(_OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.so
	rm -f main
