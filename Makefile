#Compiler and flags
CC = gcc
CFLAGS = -fopenmp -O3

TARGET = matmul

all: $(TARGET)

#build the executable
$(TARGET): matmul.c
	$(CC) $(CFLAGS) matmul.c -o $(TARGET)

clean:
	rm -f $(TARGET)