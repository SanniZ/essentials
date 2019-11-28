CC = gcc
TARGET = main
CFLAGS = -L/usr/lib/python2.7/ -lpython2.7

all: build

build:
	@$(CC) -o main main.c $(CFLAGS)

.PHONY: clean
clean:
	@rm -rf main *.o *.pyc __pycache__