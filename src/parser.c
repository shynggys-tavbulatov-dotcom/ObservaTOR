#include "parser.h"
#include "events.h"

#include <string.h>

size_t parse_line(
    const char *line,
    size_t line_number,
    ParsedEvent events[],
    size_t event_capacity
)
{
    EventType matched_events[16];
    size_t match_count;
    size_t event_index;

    if (line == NULL ||
        events == NULL ||
        event_capacity == 0) {

        return 0;
    }

    match_count = match_events(
        line,
        matched_events,
        sizeof(matched_events) / sizeof(matched_events[0])
    );

    /*
     * Do not write beyond the caller's output array.
     */
    if (match_count > event_capacity) {
        match_count = event_capacity;
    }

    for (event_index = 0;
         event_index < match_count;
         event_index++) {

        events[event_index].type =
            matched_events[event_index];

        events[event_index].line_number =
            line_number;

        /*
         * Copy the original log line into the event.
         *
         * snprintf could also be used, but this form makes
         * the truncation and terminating null byte explicit.
         */
        strncpy(
            events[event_index].raw_line,
            line,
            sizeof(events[event_index].raw_line) - 1
        );

        events[event_index]
            .raw_line[
                sizeof(events[event_index].raw_line) - 1
            ] = '\0';

        /*
         * fgets normally leaves the newline in the string.
         * Remove it so reports stay on one clean line.
         */
        events[event_index]
            .raw_line[
                strcspn(events[event_index].raw_line, "\r\n")
            ] = '\0';
    }

    return match_count;
}
