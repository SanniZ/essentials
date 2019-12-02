CUR_DIR= $(shell pwd)

CC = gcc
CFLAGS = -Wall -O

ifneq ($(PY), )
CFLAGS += -L/usr/lib/$(PY) -lpython$(PY)
TARGET = main.py.$(PY)
else
CFLAGS += -L/usr/lib/python2.7 -lpython2.7
TARGET = main
endif


SOURCES = \
	$(CUR_DIR)/main.c

OUT = out
OUT_OBJS = $(OUT)/objs

DIR_OBJS = $(patsubst %.c,%.o, $(SOURCES))
OBJS = $(addprefix $(OUT_OBJS)/, $(patsubst %.c,%.o, $(SOURCES)))

all: main

main: $(OBJS)
	@$(CC) -o $(OUT)/$(TARGET) $(OBJS) $(CFLAGS)
	@ln -s $(OUT)/$(TARGET) .

$(OBJS): $(DIR_OBJS)

$(DIR_OBJS): %.o : %.c
	@mkdir -p $(OUT_OBJS)/$(dir $@)
	@$(CC) -o main.o -c main.c $(CFLAGS)
	@mv $@ $(OUT_OBJS)/$(dir $@)

.PHONY: clean
clean:
	@rm -rf  *.o *.pyc __pycache__ $(OUT) $(TARGET)
	
.PHONY: help
help:
	@echo 'make PY=2.7 or make PY=3'
