#include "parser.h"

#include <stdio.h>

int main(void)
{
    ObservatorStats stats;

    if (parse_log_file("tests/test-data.log", &stats) != 0) {
        fprintf(stderr, "FAIL: could not read test log\n");
        return 1;
    }

    if (stats.total_lines != 7 ||
        stats.bootstrap_events != 3 ||
        stats.warnings != 2 ||
        stats.errors != 1 ||
        stats.connection_failures != 2) {
        fprintf(stderr, "FAIL: parser returned unexpected counts\n");
        fprintf(stderr,
                "received: lines=%u bootstrap=%u warnings=%u errors=%u failures=%u\n",
                stats.total_lines,
                stats.bootstrap_events,
                stats.warnings,
                stats.errors,
                stats.connection_failures);
        return 1;
    }

    printf("PASS: parser counts are correct\n");
    return 0;
}
