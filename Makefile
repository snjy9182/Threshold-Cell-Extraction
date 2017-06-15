# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
a6: a6.o
	$(CC) $(CFLAGS) -o a6 a6.o

# Compiles a6.c into an object file
a6.o: a6.c
	$(CC) $(CFLAGS) -c a6.c