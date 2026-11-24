#ifndef TWILIGHT1_MACRO_H
#define TWILIGHT1_MACRO_H

#include <stdint.h>

#define TWILIGHT1_MACRO_COUNT 6

typedef enum {
    TWILIGHT_K1_BODY = 0,
    TWILIGHT_K2_EDGE,
    TWILIGHT_K3_GROWL,
    TWILIGHT_K4_MOTION,
    TWILIGHT_K5_SPACE,
    TWILIGHT_K6_MUTATE
} twilight1_macro_id_t;

typedef struct {
    uint8_t body;
    uint8_t edge;
    uint8_t growl;
    uint8_t motion;
    uint8_t space;
    uint8_t mutate;
} twilight1_macro_values_t;

/* All macro values are constrained to 0-100. */
static inline uint8_t twilight1_macro_clamp(int value)
{
    if (value < 0)
        return 0;

    if (value > 100)
        return 100;

    return (uint8_t)value;
}

#endif
