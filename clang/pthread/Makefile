
CC = gcc
CFLAGS = -lpthread -Wall -O

# source files.
src_files = src/main.c \
            src/thread_fn.c

# .o
objs = $(patsubst %.c, %.o, $(src_files))


# target binary.
BIN = out/bin/pthreadx


# build
all: build_start build build_end

build_start:
	@$(shell mkdir -p out/objs)
	@$(shell mkdir -p out/bin)

build: $(objs)
	@$(CC) $(objs) -o $(BIN) $(CFLAGS)

build_end:
	@$(foreach var, $(objs), $(shell mkdir -p out/objs/$(shell dirname $(var)) && mv $(var) out/objs/$(shell dirname $(var))/))

# clean
.PHONY: clean
clean:
	@rm -rf out
