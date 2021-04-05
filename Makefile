CC = gcc

all: project1.c
		gcc -g -Wall -o project1 project1.c

clean:
		$(RM) project1