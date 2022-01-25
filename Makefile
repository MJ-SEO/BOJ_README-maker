CC = gcc
CFLAGS =
TARGET = maker
OBJS = 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) maker.c

clean:
	rm -rf *.o
	rm -rf maker
