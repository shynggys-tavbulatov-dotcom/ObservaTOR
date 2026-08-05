#ifndef OBSERVATOR_PARSER_H
#define OBSERVATOR_PARSER_H

typedef struct {
    unsigned int total_lines;

    unsigned int bootstrap_progress;
    unsigned int bootstrap_complete;

    unsigned int warnings;
    unsigned int errors;

    unsigned int connection_failures;
    unsigned int circuits;
    unsigned int onion_services;
} ObservatorStats;

/*
 * Read a Tor log file, detect events, and update statistics.
 *
 * Returns:
 *   0  on success
 *  -1  on invalid arguments or file error
 */
int parse_log_file(
    const char *file_path,
    ObservatorStats *stats
);

#endif
