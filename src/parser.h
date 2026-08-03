#ifndef OBSERVATOR_PARSER_H
#define OBSERVATOR_PARSER_H

typedef struct {
    unsigned int total_lines;
    unsigned int bootstrap_events;
    unsigned int warnings;
    unsigned int errors;
    unsigned int connection_failures;
} ObservatorStats;

int parse_log_file(const char *file_path, ObservatorStats *stats);

#endif
