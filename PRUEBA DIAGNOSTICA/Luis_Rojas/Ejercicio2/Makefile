CC      ?= gcc
CFLAGS  ?= -O2 -std=gnu11 -Wall -Wextra
TARGET   = pascal

all: $(TARGET)

$(TARGET): pascal.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) 5 2
	python3 pascal.py 5 2

bench: $(TARGET)
	@echo "=== C ==="
	./$(TARGET) --bench
	@echo "=== Python ==="
	python3 pascal.py --bench

clean:
	rm -f $(TARGET)

.PHONY: all run bench clean
