#include "parser.h"

#include <stdio.h>
#include <string.h>

int parse_log_file(const char *file_path, ObservatorStats *stats)
{
    FILE *log_file;
    char line[1024];

    if (file_path == NULL || stats == NULL) {
        return -1;
    }

    stats->total_lines = 0;
    stats->bootstrap_events = 0;
    stats->warnings = 0;
    stats->errors = 0;
    stats->connection_failures = 0;

    log_file = fopen(file_path, "r");

    if (log_file == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), log_file) != NULL) {
        stats->total_lines++;

        if (strstr(line, "Bootstrapped") != NULL) {
            stats->bootstrap_events++;
        }

        if (strstr(line, "[warn]") != NULL) {
            stats->warnings++;
        }

        if (strstr(line, "[err]") != NULL) {
            stats->errors++;
        }

        if (strstr(line, "connection failed") != NULL ||
            strstr(line, "Connection failed") != NULL) {
            stats->connection_failures++;
        }
    }

    fclose(log_file);
    return 0;
}
