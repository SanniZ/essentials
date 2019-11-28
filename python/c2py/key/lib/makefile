
OUT := out
OUT_OBJS := $(OUT)/objs

SOURCES = \
		src/key.c

INCLUDES = \
		includes

DIR_OBJS = $(patsubst %.c,%.o,$(SOURCES))
OBJS = $(addprefix $(OUT_OBJS)/,$(patsubst %.c,%.o,$(SOURCES)))

# vpath %.c $(addsuffix :, $(dir $(patsubst %.c,%.o,$(SOURCES)))))

CC = gcc
TARGET = libkey.so
CFLAGS = -I $(INCLUDES) -shared -fPIC -Wall -O

all: build

$(OBJS):$(DIR_OBJS)
#
$(DIR_OBJS):%.o : %.c
	@mkdir -p $(OUT_OBJS)/$(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c  $<
	@mv $@ $(OUT_OBJS)/$(dir $@)

build: $(OBJS)
	@$(CC) $(OBJS) -o $(OUT)/$(TARGET) $(CFLAGS)

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf $(OUT)
