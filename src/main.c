#include "parser.h"
#include "report.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    ObservatorStats stats;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <tor-log-file>\n", argv[0]);
        return 1;
    }

    if (parse_log_file(argv[1], &stats) != 0) {
        fprintf(stderr, "error: could not read log file: %s\n", argv[1]);
        return 1;
    }

    print_report(argv[1], &stats);

    return 0;
}
