#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "twilight1_macro.h"

#define PATCH_BYTES 156

int twilight1_engine_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    const twilight1_macro_values_t *macros);

int main(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES] = {0};

    twilight1_macro_values_t macros;

    source[16]  = 60;
    source[37]  = 70;
    source[58]  = 80;
    source[79]  = 90;
    source[100] = 50;
    source[121] = 40;

    twilight1_macro_init(&macros);

    /* EDGE is not implemented yet. */
    macros.edge = 100;

    assert(twilight1_engine_apply(
        source, output, &macros) == 0);

    /* EDGE must not affect the patch in v1. */
    assert(memcmp(source, output, PATCH_BYTES) == 0);

    printf("TWILIGHT-1 EDGE isolation test passed!\n");

    return 0;
}
