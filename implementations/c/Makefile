CC = gcc
CFLAGS = -O2 -Wall -std=c99
LDFLAGS = -lm

SRCS = main.c sorting.c matrix.c aes.c dijkstra.c
OBJS = $(SRCS:.c=.o)
TARGET = benchmark

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
