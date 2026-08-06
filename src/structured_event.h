#ifndef OBSERVATOR_STRUCTURED_EVENT_H
#define OBSERVATOR_STRUCTURED_EVENT_H

#include "events.h"

#include <stddef.h>

#define EVENT_RAW_LINE_LENGTH 1024
#define EVENT_TIMESTAMP_LENGTH 32

typedef struct {
    EventType type;
    EventSeverity severity;
    EventSubsystem subsystem;

    size_t line_number;

    char timestamp[EVENT_TIMESTAMP_LENGTH];
    char raw_line[EVENT_RAW_LINE_LENGTH];
} ParsedEvent;

const char *event_severity_name(EventSeverity severity);
const char *event_subsystem_name(EventSubsystem subsystem);

#endif
