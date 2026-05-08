#Compiler and flags
CC = gcc
CFLAGS = -fopenmp -O3

TARGET = matmul

#List of thread counts to test for strong scaling
THREADS = 1 2 4 8 16

all: $(TARGET)

#build the executable
$(TARGET): matmul.c
	$(CC) $(CFLAGS) matmul.c -o $(TARGET)

clean:
	rm -f $(TARGET)