# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
CellExtraction: CellExtraction.o
	$(CC) $(CFLAGS) -o CellExtraction CellExtraction.o

# Compiles CellExtraction.c into an object file
CellExtraction.o: CellExtraction.c
	$(CC) $(CFLAGS) -c CellExtraction.c