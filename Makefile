CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Isrc
TARGET = build/observator
SOURCES = src/main.c src/reader.c src/parser.c src/events.c src/report.c
TEST_TARGET = build/test_parser
TEST_SOURCES = tests/test_parser.c src/parser.c src/events.c
EVENT_TEST_TARGET = build/test_events
EVENT_TEST_SOURCES = tests/test_events.c src/events.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) examples/sample-tor.log

clean:
	rm -f $(TARGET) \
	      $(TEST_TARGET) \
	      $(EVENT_TEST_TARGET)

test: $(TEST_TARGET) $(EVENT_TEST_TARGET)
	./$(TEST_TARGET)
	./$(EVENT_TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)
$(EVENT_TEST_TARGET): $(EVENT_TEST_SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(EVENT_TEST_SOURCES) -o $(EVENT_TEST_TARGET)
.PHONY: all run test clean
