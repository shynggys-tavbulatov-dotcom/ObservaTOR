#include "reader.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>

#define READER_LINE_LENGTH 1024
#define EVENTS_PER_LINE 16

int read_log_file(
    const char *file_path,
    ParsedEvent events[],
    size_t event_capacity,
    ReaderResult *result
)
{
    FILE *log_file;
    char line[READER_LINE_LENGTH];

    if (file_path == NULL ||
        events == NULL ||
        result == NULL ||
        event_capacity == 0) {

        return -1;
    }

    memset(result, 0, sizeof(*result));

    log_file = fopen(file_path, "r");

    if (log_file == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), log_file) != NULL) {
        ParsedEvent line_events[EVENTS_PER_LINE];
        size_t line_event_count;
        size_t event_index;

        result->total_lines++;

        line_event_count = parse_line(
            line,
            result->total_lines,
            line_events,
            EVENTS_PER_LINE
        );

        for (event_index = 0;
             event_index < line_event_count;
             event_index++) {

            if (result->event_count >= event_capacity) {
                result->event_capacity_reached = 1;
                fclose(log_file);
                return 0;
            }

            events[result->event_count] =
                line_events[event_index];

            result->event_count++;
        }
    }

    fclose(log_file);

    return 0;
}
