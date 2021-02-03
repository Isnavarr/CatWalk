# Usage:
# change Home to point to the directory where all of your items are
# add this directory also to your LD_LIBRARY_PATH by running after you make
# export LD_LIBRARY_PATH=$HOME:$LD_LIBRARY_PATH

_OBJS = math.o print.o

CFLAGS += -Wall -Werror -fPIC

LIB = shared

SHARED_LIB = lib$(LIB).so

HOME = /home/jessicalam/Desktop/CatWalk/jess_toy/

#LD_LIBRARY_PATH += $(HOME)

.PHONY: all

all: $(SHARED_LIB)
	$(CC) -L $(HOME) -Wall main.c -o main -l $(LIB)

$(SHARED_LIB): $(_OBJS)
	$(CC) -shared -o $(SHARED_LIB) $(_OBJS)

$(_OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.so
	rm -f main
