#include "parser.h"

#include <stdio.h>
#include <string.h>

#define TEST_EVENT_CAPACITY 16

static int test_warning_and_connection_failure(void)
{
    const char *line =
        "Aug 05 17:00:02 [warn] connection failed while opening Circuit\n";

    ParsedEvent events[TEST_EVENT_CAPACITY];
    size_t event_count;

    event_count = parse_line(
        line,
        3,
        events,
        TEST_EVENT_CAPACITY
    );

    if (event_count != 3) {
        fprintf(
            stderr,
            "expected 3 events, got %zu\n",
            event_count
        );

        return 1;
    }

    if (events[0].type != EVENT_WARNING) {
        fprintf(stderr, "expected first event to be warning\n");
        return 1;
    }

    if (events[1].type != EVENT_CONNECTION_FAILURE) {
        fprintf(
            stderr,
            "expected second event to be connection failure\n"
        );

        return 1;
    }

    if (events[2].type != EVENT_CIRCUIT) {
        fprintf(stderr, "expected third event to be circuit\n");
        return 1;
    }

    if (events[0].line_number != 3 ||
        events[1].line_number != 3 ||
        events[2].line_number != 3) {

        fprintf(stderr, "incorrect line number\n");
        return 1;
    }

    if (strchr(events[0].raw_line, '\n') != NULL) {
        fprintf(stderr, "raw line still contains newline\n");
        return 1;
    }

    return 0;
}

static int test_bootstrap_complete(void)
{
    const char *line =
        "Aug 05 17:00:01 [notice] Bootstrapped 100%: Done\n";

    ParsedEvent events[TEST_EVENT_CAPACITY];
    size_t event_count;

    event_count = parse_line(
        line,
        2,
        events,
        TEST_EVENT_CAPACITY
    );

    if (event_count != 2) {
        fprintf(
            stderr,
            "expected 2 bootstrap events, got %zu\n",
            event_count
        );

        return 1;
    }

    if (events[0].type != EVENT_BOOTSTRAP_COMPLETE) {
        fprintf(
            stderr,
            "expected first event to be bootstrap complete\n"
        );

        return 1;
    }

    if (events[1].type != EVENT_BOOTSTRAP_PROGRESS) {
        fprintf(
            stderr,
            "expected second event to be bootstrap progress\n"
        );

        return 1;
    }

    return 0;
}

static int test_unknown_line(void)
{
    const char *line =
        "Aug 05 17:00:04 [notice] ordinary Tor log message\n";

    ParsedEvent events[TEST_EVENT_CAPACITY];
    size_t event_count;

    event_count = parse_line(
        line,
        5,
        events,
        TEST_EVENT_CAPACITY
    );

    if (event_count != 0) {
        fprintf(
            stderr,
            "expected 0 events, got %zu\n",
            event_count
        );

        return 1;
    }

    return 0;
}

static int test_invalid_arguments(void)
{
    ParsedEvent events[TEST_EVENT_CAPACITY];

    if (parse_line(NULL, 1, events, TEST_EVENT_CAPACITY) != 0) {
        fprintf(stderr, "NULL line should return 0\n");
        return 1;
    }

    if (parse_line("test", 1, NULL, TEST_EVENT_CAPACITY) != 0) {
        fprintf(stderr, "NULL event array should return 0\n");
        return 1;
    }

    if (parse_line("test", 1, events, 0) != 0) {
        fprintf(stderr, "zero capacity should return 0\n");
        return 1;
    }

    return 0;
}

int main(void)
{
    if (test_warning_and_connection_failure() != 0) {
        return 1;
    }

    if (test_bootstrap_complete() != 0) {
        return 1;
    }

    if (test_unknown_line() != 0) {
        return 1;
    }

    if (test_invalid_arguments() != 0) {
        return 1;
    }

    printf("parser tests passed\n");

    return 0;
}
