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
    printf("bootstrap progress:  %u\n", stats->bootstrap_progress);
    printf("bootstrap complete:  %u\n", stats->bootstrap_complete);
    printf("warnings: %u\n", stats->warnings);
    printf("errors: %u\n", stats->errors);
    printf("connection failures: %u\n", stats->connection_failures);
    printf("circuits:            %u\n", stats->circuits);
    printf("onion services:      %u\n", stats->onion_services);
}
