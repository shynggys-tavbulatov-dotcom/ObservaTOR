#include "structured_event.h"

const char *event_severity_name(EventSeverity severity)
{
    switch (severity) {
        case EVENT_SEVERITY_INFO:
            return "info";

        case EVENT_SEVERITY_WARNING:
            return "warning";

        case EVENT_SEVERITY_ERROR:
            return "error";

        case EVENT_SEVERITY_UNKNOWN:
        default:
            return "unknown";
    }
}

const char *event_subsystem_name(EventSubsystem subsystem)
{
    switch (subsystem) {
        case EVENT_SUBSYSTEM_BOOTSTRAP:
            return "bootstrap";

        case EVENT_SUBSYSTEM_GENERAL:
            return "general";

        case EVENT_SUBSYSTEM_NETWORK:
            return "network";

        case EVENT_SUBSYSTEM_CIRCUIT:
            return "circuit";

        case EVENT_SUBSYSTEM_ONION_SERVICE:
            return "onion service";

        case EVENT_SUBSYSTEM_UNKNOWN:
        default:
            return "unknown";
    }
}
