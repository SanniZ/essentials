
CC = gcc
MDKEY_SO = mdkey.so
CFLAGS = -shared -fPIC
OUT := out
OUT_OBJS := $(OUT)/objs

src = \
	key.c

objs = $(patsubst %.c, %.o, $(src))

all: build_start build build_end

build_start:
	@mkdir -p $(OUT)

build: $(objs)
	@$(CC) $(objs) -o $(OUT)/$(MDKEY_SO) $(CFLAGS)

build_end:
	@$(foreach var, $(objs), $(shell mkdir -p $(OUT_OBJS)/$(shell dirname $(var)) && mv $(var) $(OUT_OBJS)/$(shell dirname $(var))/))

.PHONY: clean
clean:
	@rm -rf $(OUT)