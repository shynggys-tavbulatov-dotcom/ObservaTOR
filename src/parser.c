#include "parser.h"
#include "events.h"

#include <stdio.h>
#include <string.h>

#define MATCHED_EVENT_CAPACITY 16

static EventSeverity severity_for_event(EventType type)
{
    switch (type) {
        case EVENT_WARNING:
            return EVENT_SEVERITY_WARNING;

        case EVENT_ERROR:
        case EVENT_CONNECTION_FAILURE:
            return EVENT_SEVERITY_ERROR;

        case EVENT_BOOTSTRAP_PROGRESS:
        case EVENT_BOOTSTRAP_COMPLETE:
        case EVENT_CIRCUIT:
        case EVENT_ONION_SERVICE:
            return EVENT_SEVERITY_INFO;

        case EVENT_UNKNOWN:
        default:
            return EVENT_SEVERITY_UNKNOWN;
    }
}

static EventSubsystem subsystem_for_event(EventType type)
{
    switch (type) {
        case EVENT_BOOTSTRAP_PROGRESS:
        case EVENT_BOOTSTRAP_COMPLETE:
            return EVENT_SUBSYSTEM_BOOTSTRAP;

        case EVENT_WARNING:
        case EVENT_ERROR:
            return EVENT_SUBSYSTEM_GENERAL;

        case EVENT_CONNECTION_FAILURE:
            return EVENT_SUBSYSTEM_NETWORK;

        case EVENT_CIRCUIT:
            return EVENT_SUBSYSTEM_CIRCUIT;

        case EVENT_ONION_SERVICE:
            return EVENT_SUBSYSTEM_ONION_SERVICE;

        case EVENT_UNKNOWN:
        default:
            return EVENT_SUBSYSTEM_UNKNOWN;
    }
}

/*
 * Extract the first three whitespace-separated fields.
 *
 * Example:
 *
 * Aug 05 17:00:02 [warn] message
 *
 * becomes:
 *
 * Aug 05 17:00:02
 */
static void extract_timestamp(
    const char *line,
    char timestamp[],
    size_t timestamp_capacity
)
{
    char month[4];
    char day[3];
    char time_value[9];

    if (line == NULL ||
        timestamp == NULL ||
        timestamp_capacity == 0) {

        return;
    }

    timestamp[0] = '\0';

    if (sscanf(
            line,
            "%3s %2s %8s",
            month,
            day,
            time_value
        ) != 3) {

        return;
    }

    snprintf(
        timestamp,
        timestamp_capacity,
        "%s %s %s",
        month,
        day,
        time_value
    );
}

static void copy_raw_line(
    const char *line,
    char destination[],
    size_t destination_capacity
)
{
    if (line == NULL ||
        destination == NULL ||
        destination_capacity == 0) {

        return;
    }

    strncpy(
        destination,
        line,
        destination_capacity - 1
    );

    destination[destination_capacity - 1] = '\0';

    destination[
        strcspn(destination, "\r\n")
    ] = '\0';
}

size_t parse_line(
    const char *line,
    size_t line_number,
    ParsedEvent events[],
    size_t event_capacity
)
{
    EventType matched_events[MATCHED_EVENT_CAPACITY];
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
        MATCHED_EVENT_CAPACITY
    );

    if (match_count > event_capacity) {
        match_count = event_capacity;
    }

    for (event_index = 0;
         event_index < match_count;
         event_index++) {

        ParsedEvent *event = &events[event_index];

        event->type = matched_events[event_index];

        event->severity =
            severity_for_event(event->type);

        event->subsystem =
            subsystem_for_event(event->type);

        event->line_number = line_number;

        extract_timestamp(
            line,
            event->timestamp,
            sizeof(event->timestamp)
        );

        copy_raw_line(
            line,
            event->raw_line,
            sizeof(event->raw_line)
        );
    }

    return match_count;
}
