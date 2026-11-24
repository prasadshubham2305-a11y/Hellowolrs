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
    uint8_t original[PATCH_BYTES];

    twilight1_macro_values_t macros;

    source[16]  = 80;
    source[37]  = 80;
    source[58]  = 80;
    source[79]  = 80;
    source[100] = 80;
    source[121] = 80;

    memcpy(original, source, PATCH_BYTES);

    twilight1_macro_init(&macros);

    /* Neutral engine */
    assert(twilight1_engine_apply(
        source, output, &macros) == 0);

    assert(memcmp(source, output, PATCH_BYTES) == 0);

    /* BODY transformation */
    macros.body = 50;

    assert(twilight1_engine_apply(
        source, output, &macros) == 0);

    assert(output[16] == 88);
    assert(output[37] == 88);
    assert(output[58] == 88);
    assert(output[79] == 88);
    assert(output[100] == 88);
    assert(output[121] == 88);

    /* Original remains unchanged */
    assert(memcmp(source, original, PATCH_BYTES) == 0);

    /* Invalid pointers */
    assert(twilight1_engine_apply(
        NULL, output, &macros) == -1);

    assert(twilight1_engine_apply(
        source, NULL, &macros) == -1);

    assert(twilight1_engine_apply(
        source, output, NULL) == -1);

    printf("TWILIGHT-1 Engine tests passed!\n");

    return 0;
}
