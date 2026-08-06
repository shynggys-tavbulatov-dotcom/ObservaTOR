#ifndef OBSERVATOR_STRUCTURED_EVENT_H
#define OBSERVATOR_STRUCTURED_EVENT_H

#include "events.h"

#include <stddef.h>

#define EVENT_RAW_LINE_LENGTH 1024

typedef struct {
    EventType type;

    /*
     * Line number inside the original log file.
     */
    size_t line_number;

    /*
     * Complete original line that caused the event.
     */
    char raw_line[EVENT_RAW_LINE_LENGTH];
} ParsedEvent;

#endif
