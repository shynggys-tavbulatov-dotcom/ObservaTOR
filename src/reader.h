#ifndef OBSERVATOR_READER_H
#define OBSERVATOR_READER_H

#include "structured_event.h"

#include <stddef.h>

typedef struct {
    size_t total_lines;
    size_t event_count;
    int event_capacity_reached;
} ReaderResult;

/*
 * Read a log file and store parsed events.
 *
 * Returns:
 *   0  on success
 *  -1  on invalid arguments or file error
 */
int read_log_file(
    const char *file_path,
    ParsedEvent events[],
    size_t event_capacity,
    ReaderResult *result
);

#endif
