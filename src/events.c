#include "events.h"
#include <string.h>

static const EventRule EVENT_RULES[] = {
    {
        EVENT_BOOTSTRAP_COMPLETE,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_BOOTSTRAP,
        100,
        "Bootstrapped 100%"
    },
    {
        EVENT_BOOTSTRAP_PROGRESS,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_BOOTSTRAP,
        10,
        "Bootstrapped"
    },
    {
        EVENT_WARNING,
        EVENT_SEVERITY_WARNING,
        EVENT_SUBSYSTEM_GENERAL,
        50,
        "[warn]"
    },
    {
        EVENT_ERROR,
        EVENT_SEVERITY_ERROR,
        EVENT_SUBSYSTEM_GENERAL,
        50,
        "[err]"
    },
    {
        EVENT_CONNECTION_FAILURE,
        EVENT_SEVERITY_ERROR,
        EVENT_SUBSYSTEM_NETWORK,
        80,
        "connection failed"
    },
    {
        EVENT_CONNECTION_FAILURE,
        EVENT_SEVERITY_ERROR,
        EVENT_SUBSYSTEM_NETWORK,
        80,
        "Connection failed"
    },
    {
        EVENT_CIRCUIT,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_CIRCUIT,
        40,
        "Circuit"
    },
    {
        EVENT_CIRCUIT,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_CIRCUIT,
        40,
        "circuit"
    },
    {
        EVENT_ONION_SERVICE,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_ONION_SERVICE,
        60,
        "Onion service"
    },
    {
        EVENT_ONION_SERVICE,
        EVENT_SEVERITY_INFO,
        EVENT_SUBSYSTEM_ONION_SERVICE,
        60,
        "onion service"
    }
};

static const size_t EVENT_RULE_COUNT =
    sizeof(EVENT_RULES) / sizeof(EVENT_RULES[0]);

size_t match_events(
    const char *line,
    const EventRule *events[],
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

            events[match_count] = &EVENT_RULES[rule_index];
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
