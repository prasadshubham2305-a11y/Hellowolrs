#include <stdint.h>
#include "twilight1_macro.h"

#define TWILIGHT1_PATCH_BYTES 156

void twilight1_body_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    unsigned body);

void twilight1_edge_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    unsigned edge);

/* Engine Core v2: BODY -> EDGE */
int twilight1_engine_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    const twilight1_macro_values_t *macros)
{
    if (!source || !output || !macros)
        return -1;

    uint8_t body_patch[TWILIGHT1_PATCH_BYTES];

    twilight1_body_apply(
        source,
        body_patch,
        macros->body);

    twilight1_edge_apply(
        body_patch,
        output,
        macros->edge);

    return 0;
}
