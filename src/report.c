#include "report.h"
#include "events.h"

#include <stdio.h>

typedef struct {
    unsigned int bootstrap_progress;
    unsigned int bootstrap_complete;
    unsigned int warnings;
    unsigned int errors;
    unsigned int connection_failures;
    unsigned int circuits;
    unsigned int onion_services;
} ReportStats;

static void count_event(
    EventType type,
    ReportStats *stats
)
{
    switch (type) {
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

static void print_event(
    const ParsedEvent *event,
    size_t event_number
)
{
    printf(
        "[%03zu] line %-4zu "
        "%-8s "
        "%-14s "
        "%-20s "
        "%-15s "
        "%s\n",
        event_number,
        event->line_number,
        event_severity_name(event->severity),
        event_subsystem_name(event->subsystem),
        event_type_name(event->type),
        event->timestamp,
        event->raw_line
    );
}


void print_report(
    const char *file_path,
    const ParsedEvent events[],
    size_t event_count,
    const ReaderResult *reader_result
)
{
    ReportStats stats = {0};
    size_t event_index;

    if (file_path == NULL ||
        events == NULL ||
        reader_result == NULL) {

        return;
    }

    printf("ObservaTOR report\n\n");

    printf("log file: %s\n", file_path);
    printf("lines processed: %zu\n", reader_result->total_lines);
    printf("events detected: %zu\n\n", event_count);

    printf("structured events\n");
    printf("=================\n");
printf(
    "                 "
    "%-8s "
    "%-14s "
    "%-20s "
    "%-15s "
    "%s\n",
    "severity",
    "subsystem",
    "event type",
    "timestamp",
    "raw event"
);
    for (event_index = 0;
         event_index < event_count;
         event_index++) {

        print_event(
            &events[event_index],
            event_index + 1
        );

        count_event(
            events[event_index].type,
            &stats
        );
    }

    printf("\nsummary\n");
    printf("=======\n");

    printf(
        "bootstrap progress:  %u\n",
        stats.bootstrap_progress
    );

    printf(
        "bootstrap complete:  %u\n",
        stats.bootstrap_complete
    );

    printf(
        "warnings:            %u\n",
        stats.warnings
    );

    printf(
        "errors:              %u\n",
        stats.errors
    );

    printf(
        "connection failures: %u\n",
        stats.connection_failures
    );

    printf(
        "circuits:            %u\n",
        stats.circuits
    );

    printf(
        "onion services:      %u\n",
        stats.onion_services
    );

    if (reader_result->event_capacity_reached) {
        printf(
            "\nwarning: event storage capacity was reached\n"
        );
    }
}
