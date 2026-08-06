#ifndef OBSERVATOR_REPORT_H
#define OBSERVATOR_REPORT_H

#include "reader.h"
#include "structured_event.h"

#include <stddef.h>

void print_report(
    const char *file_path,
    const ParsedEvent events[],
    size_t event_count,
    const ReaderResult *reader_result
);

#endif
