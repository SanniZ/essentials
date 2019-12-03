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

C_FILES = \
	main.c

PY_FILES = func.py

DIST = dist
DIST_OBJS = $(DIST)/objs

DIR_OBJS = $(patsubst %.c,%.o, $(C_FILES))
OBJS = $(addprefix $(DIST_OBJS)/, $(patsubst %.c,%.o, $(C_FILES)))

all: build_c build_py

build_c: $(OBJS)
	@$(CC) -o $(DIST)/$(TARGET) $(OBJS) $(CFLAGS)

build_py:
	$(shell cp $(PY_FILES) $(DIST))

$(OBJS): $(DIR_OBJS)

$(DIR_OBJS): %.o : %.c
	@mkdir -p $(DIST_OBJS)/$(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS)
	@mv $@ $(DIST_OBJS)/$(dir $@)

.PHONY: clean
clean:
	@rm -rf  *.o *.pyc __pycache__ $(DIST) $(TARGET)
	
.PHONY: help
help:
	@echo 'make PY=2.7 or make PY=3'
