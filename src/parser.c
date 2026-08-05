#include "parser.h"
#include "events.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_EVENTS_PER_LINE 16

/*
 * Reset every counter before parsing a new file.
 */
static void reset_stats(ObservatorStats *stats)
{
    memset(stats, 0, sizeof(*stats));
}

/*
 * Consume one event produced by the event engine.
 *
 * The event engine decides WHAT happened.
 * The parser decides WHAT TO DO with that event.
 */
static void consume_event(
    EventType event,
    ObservatorStats *stats
)
{
    switch (event) {
        case EVENT_BOOTSTRAP_PROGRESS:
            stats->bootstrap_progress++;
            break;

        case EVENT_BOOTSTRAP_COMPLETE:
            stats->bootstrap_complete++;
            break;

        case EVENT_WARNING:
            stats->warnings++;
            break;

        case EVENT_ERROR:
            stats->errors++;
            break;

        case EVENT_CONNECTION_FAILURE:
            stats->connection_failures++;
            break;

        case EVENT_CIRCUIT:
            stats->circuits++;
            break;

        case EVENT_ONION_SERVICE:
            stats->onion_services++;
            break;

        case EVENT_UNKNOWN:
        default:
            break;
    }
}

/*
 * Parse one line.
 *
 * match_events() is the producer.
 * consume_event() is the consumer.
 */
static void parse_line(
    const char *line,
    ObservatorStats *stats
)
{
    EventType events[MAX_EVENTS_PER_LINE];
    size_t event_count;
    size_t event_index;

    event_count = match_events(
        line,
        events,
        MAX_EVENTS_PER_LINE
    );

    for (event_index = 0;
         event_index < event_count;
         event_index++) {

        consume_event(events[event_index], stats);
    }
}

int parse_log_file(
    const char *file_path,
    ObservatorStats *stats
)
{
    FILE *log_file;
    char line[MAX_LINE_LENGTH];

    if (file_path == NULL || stats == NULL) {
        return -1;
    }

    reset_stats(stats);

    log_file = fopen(file_path, "r");

    if (log_file == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), log_file) != NULL) {
        stats->total_lines++;

        parse_line(line, stats);
    }

    fclose(log_file);

    return 0;
}
