#ifndef EVENTS_H
#define EVENTS_H

#include <stddef.h>

typedef enum {
    EVENT_UNKNOWN = 0,

    EVENT_BOOTSTRAP_PROGRESS,
    EVENT_BOOTSTRAP_COMPLETE,

    EVENT_WARNING,
    EVENT_ERROR,

    EVENT_CONNECTION_FAILURE,
    EVENT_CIRCUIT,

    EVENT_ONION_SERVICE
} EventType;

typedef enum {
    EVENT_SEVERITY_UNKNOWN = 0,
    EVENT_SEVERITY_INFO,
    EVENT_SEVERITY_WARNING,
    EVENT_SEVERITY_ERROR
} EventSeverity;

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
    int priority;
    const char *pattern;
} EventRule;

size_t match_events(
    const char *line,
    const EventRule *events[],
    size_t event_capacity
);

const char *event_type_name(EventType type);

#endif
