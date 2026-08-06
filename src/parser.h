#ifndef OBSERVATOR_PARSER_H
#define OBSERVATOR_PARSER_H

#include "structured_event.h"

#include <stddef.h>

/*
 * Parse one log line into structured events.
 *
 * One line may produce multiple events.
 *
 * Returns the number of ParsedEvent objects written
 * into the events array.
 */
size_t parse_line(
    const char *line,
    size_t line_number,
    ParsedEvent events[],
    size_t event_capacity
);

#endif
