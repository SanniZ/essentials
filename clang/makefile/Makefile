
CC = gcc
CFLAGS = -Wall -O


OUT = out
TARGET = $(OUT)/main
OUT_OBJS = $(OUT)/objs
OUT_OBJS_SRC = $(OUT_OBJS)/$(dir $(OBJS))

SRC = src
INCLUDES = includes

C_FILES = $(wildcard $(SRC)/*.c)

OBJS = $(patsubst %.c, %.o, $(C_FILES))

all: main objs

main: $(OBJS)
	@$(shell mkdir $(OUT))
	@$(shell mkdir $(OUT_OBJS))
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)	
	chmod a+x $(TARGET)

objs:
	$(shell mkdir $(OUT_OBJS_SRC))
	$(shell mv $(dir $(OBJS))/*.o $(OUT_OBJS_SRC))

clean:
	rm -rf $(OUT)
