#ifndef OBSERVATOR_STRUCTURED_EVENT_H
#define OBSERVATOR_STRUCTURED_EVENT_H

#include "events.h"

#include <stddef.h>

#define EVENT_RAW_LINE_LENGTH 1024
#define EVENT_TIMESTAMP_LENGTH 32

/*
 * General seriousness of an event.
 */
typedef enum {
    EVENT_SEVERITY_UNKNOWN = 0,
    EVENT_SEVERITY_INFO,
    EVENT_SEVERITY_WARNING,
    EVENT_SEVERITY_ERROR
} EventSeverity;

/*
 * ObservaTOR subsystem associated with an event.
 */
typedef enum {
    EVENT_SUBSYSTEM_UNKNOWN = 0,
    EVENT_SUBSYSTEM_BOOTSTRAP,
    EVENT_SUBSYSTEM_GENERAL,
    EVENT_SUBSYSTEM_NETWORK,
    EVENT_SUBSYSTEM_CIRCUIT,
    EVENT_SUBSYSTEM_ONION_SERVICE
} EventSubsystem;

typedef struct {
    EventType type;
    EventSeverity severity;
    EventSubsystem subsystem;

    size_t line_number;

    char timestamp[EVENT_TIMESTAMP_LENGTH];
    char raw_line[EVENT_RAW_LINE_LENGTH];
} ParsedEvent;

/*
 * Return readable metadata names for reports and exports.
 */
const char *event_severity_name(EventSeverity severity);
const char *event_subsystem_name(EventSubsystem subsystem);

#endif
