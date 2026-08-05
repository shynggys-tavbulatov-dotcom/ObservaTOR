#ifndef EVENTS_H
#define EVENTS_H

#include <stddef.h>

typedef enum {
    EVENT_UNKNOWN = 0,

    /* Bootstrap */
    EVENT_BOOTSTRAP_PROGRESS,
    EVENT_BOOTSTRAP_COMPLETE,

    /* General */
    EVENT_WARNING,
    EVENT_ERROR,

    /* Network */
    EVENT_CONNECTION_FAILURE,
    EVENT_CIRCUIT,

    /* Hidden services */
    EVENT_ONION_SERVICE
} EventType;

typedef struct {
    EventType type;
    const char *pattern;
} EventRule;

/*
 * Match one log line against all known event rules.
 *
 * Matching event types are written into the events array.
 * Returns the number of events written.
 */
size_t match_events(
    const char *line,
    EventType events[],
    size_t event_capacity
);

/*
 * Return a readable name for an event type.
 */
const char *event_type_name(EventType type);

#endif
