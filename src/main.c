#include "parser.h"
#include "report.h"

#include <stdio.h>
#include <string.h>

static void print_help(const char *program_name)
{
    printf("ObservaTOR - lightweight Tor log analyzer\n\n");
    printf("usage:\n");
    printf("  %s <tor-log-file>\n", program_name);
    printf("  %s --help\n", program_name);
    printf("  %s --version\n\n", program_name);
    printf("options:\n");
    printf("  -h, --help       show this help message\n");
    printf("  -v, --version    show program version\n");
}

int main(int argc, char *argv[])
{
    ObservatorStats stats;

    if (argc == 2 &&
        (strcmp(argv[1], "--help") == 0 ||
         strcmp(argv[1], "-h") == 0)) {
        print_help(argv[0]);
        return 0;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "--version") == 0 ||
         strcmp(argv[1], "-v") == 0)) {
        printf("ObservaTOR 0.1.0\n");
        return 0;
    }

    if (argc != 2) {
        fprintf(stderr, "usage: %s <tor-log-file>\n", argv[0]);
        fprintf(stderr, "try '%s --help' for more information\n", argv[0]);
        return 1;
    }

    if (parse_log_file(argv[1], &stats) != 0) {
        fprintf(stderr,
                "error: could not read log file: %s\n",
                argv[1]);
        return 1;
    }

    print_report(argv[1], &stats);

    return 0;
}
