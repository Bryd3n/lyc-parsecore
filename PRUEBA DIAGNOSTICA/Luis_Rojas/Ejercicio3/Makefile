CC      ?= gcc
CFLAGS  ?= -O2 -std=gnu11 -Wall -Wextra
TARGET   = traductor

all: $(TARGET)

$(TARGET): traductor.c
	$(CC) $(CFLAGS) -o $@ $<

demo: $(TARGET)
	./$(TARGET) ejemplo.c > traducido.c
	@echo "--- Archivo generado: traducido.c ---"
	@cat traducido.c

clean:
	rm -f $(TARGET) traducido.c

.PHONY: all demo clean
