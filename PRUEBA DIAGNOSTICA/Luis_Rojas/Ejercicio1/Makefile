CC      ?= gcc
CFLAGS  ?= -O2 -std=gnu11 -Wall -Wextra
TARGET   = caballo

all: $(TARGET)

$(TARGET): caballo.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

bench: $(TARGET)
	./$(TARGET) --bench

clean:
	rm -f $(TARGET)

.PHONY: all run bench clean
