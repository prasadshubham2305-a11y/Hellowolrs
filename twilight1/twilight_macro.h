#ifndef TWILIGHT_MACRO_H
#define TWILIGHT_MACRO_H

#include <stdint.h>

#define TWILIGHT_MACRO_MAX 100

typedef struct {
    uint8_t body;
    uint8_t edge;
    uint8_t growl;
    uint8_t motion;
    uint8_t space;
    uint8_t mutate;
} twilight_macros_t;

void twilight_macros_init(twilight_macros_t *macros);

#endif
