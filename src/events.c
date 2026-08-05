#include "events.h"

#include <string.h>

static const EventRule EVENT_RULES[] = {
    { EVENT_BOOTSTRAP_COMPLETE, "Bootstrapped 100%" },
    { EVENT_BOOTSTRAP_PROGRESS, "Bootstrapped" },
    { EVENT_WARNING,            "[warn]" },
    { EVENT_ERROR,              "[err]" },
    { EVENT_CONNECTION_FAILURE, "connection failed" },
    { EVENT_CONNECTION_FAILURE, "Connection failed" },
    { EVENT_CIRCUIT,            "Circuit" },
    { EVENT_CIRCUIT,            "circuit" },
    { EVENT_ONION_SERVICE,      "onion service" },
    { EVENT_ONION_SERVICE,      "Onion service" }
};

static const size_t EVENT_RULE_COUNT =
    sizeof(EVENT_RULES) / sizeof(EVENT_RULES[0]);

size_t match_events(
    const char *line,
    EventType events[],
    size_t event_capacity
)
{
    size_t match_count = 0;
    size_t rule_index;

    if (line == NULL || events == NULL || event_capacity == 0) {
        return 0;
    }

    for (rule_index = 0;
         rule_index < EVENT_RULE_COUNT;
         rule_index++) {

        if (strstr(line, EVENT_RULES[rule_index].pattern) != NULL) {
            if (match_count >= event_capacity) {
                break;
            }

            events[match_count] = EVENT_RULES[rule_index].type;
            match_count++;
        }
    }

    return match_count;
}

const char *event_type_name(EventType type)
{
    switch (type) {
        case EVENT_BOOTSTRAP_PROGRESS:
            return "bootstrap progress";

        case EVENT_BOOTSTRAP_COMPLETE:
            return "bootstrap complete";

        case EVENT_WARNING:
            return "warning";

        case EVENT_ERROR:
            return "error";

        case EVENT_CONNECTION_FAILURE:
            return "connection failure";

        case EVENT_CIRCUIT:
            return "circuit";

        case EVENT_ONION_SERVICE:
            return "onion service";

        case EVENT_UNKNOWN:
        default:
            return "unknown";
    }
}
