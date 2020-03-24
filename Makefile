CC = gcc
LD = gcc

SRCS = $(wildcard *.c)
OBJS = $(patsubst %c, %o, $(SRCS))
INCLUDE += .

TARGET = test-demo

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LIB)
 
%o: %c
	$(CC) -c $^ $(INCLUDE) $(CFLAGS) 

clean:
	rm -f $(OBJS) $(TARGET)

test:
	make
	rm -f $(OBJS)
	./$(TARGET)