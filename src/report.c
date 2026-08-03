#include "report.h"

#include <stdio.h>

void print_report(const char *file_path, const ObservatorStats *stats)
{
    if (file_path == NULL || stats == NULL) {
        return;
    }

    printf("ObservaTOR report\n\n");
    printf("log file: %s\n", file_path);
    printf("lines processed: %u\n\n", stats->total_lines);
    printf("bootstrap events: %u\n", stats->bootstrap_events);
    printf("warnings: %u\n", stats->warnings);
    printf("errors: %u\n", stats->errors);
    printf("connection failures: %u\n", stats->connection_failures);
}
