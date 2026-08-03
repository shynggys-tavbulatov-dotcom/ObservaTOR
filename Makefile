CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Isrc
TARGET = build/observator
SOURCES = src/main.c src/parser.c src/report.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) examples/sample-tor.log

clean:
	rm -f $(TARGET)

.PHONY: all run clean
