#include "events.h"

#include <stdio.h>

static int contains_event(
    const EventRule *events[],
    size_t count,
    EventType expected
)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (events[i]->type == expected) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const EventRule *events[8];
    size_t count;

    count = match_events(
        "[notice] Bootstrapped 100%: Done",
        events,
        8
    );

    if (!contains_event(
            events,
            count,
            EVENT_BOOTSTRAP_COMPLETE
        )) {

        puts("FAIL: bootstrap complete");
        return 1;
    }

    if (!contains_event(
            events,
            count,
            EVENT_BOOTSTRAP_PROGRESS
        )) {

        puts("FAIL: bootstrap progress");
        return 1;
    }

    count = match_events(
        "[warn] Onion service connection failed",
        events,
        8
    );

    if (!contains_event(events, count, EVENT_WARNING)) {
        puts("FAIL: warning");
        return 1;
    }

    if (!contains_event(
            events,
            count,
            EVENT_CONNECTION_FAILURE
        )) {

        puts("FAIL: connection failure");
        return 1;
    }

    if (!contains_event(
            events,
            count,
            EVENT_ONION_SERVICE
        )) {

        puts("FAIL: onion service");
        return 1;
    }

    puts("PASS: event engine");

    return 0;
}
