CC = gcc
TARGET = main
CFLAGS = -L/usr/lib/python3.5/ -lpython3.5m -ldl -Wall -O

all: build

build:
	@$(CC) -o main main.c $(CFLAGS)

.PHONY: clean
clean:
	@rm -rf main *.o *.pyc __pycache__
