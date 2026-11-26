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

void twilight1_growl_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    unsigned growl);

/* Engine Core v3: BODY -> EDGE -> GROWL */
int twilight1_engine_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    const twilight1_macro_values_t *macros)
{
    if (!source || !output || !macros)
        return -1;

    uint8_t body_patch[TWILIGHT1_PATCH_BYTES];
    uint8_t edge_patch[TWILIGHT1_PATCH_BYTES];

    /* Stage 1: BODY */
    twilight1_body_apply(
        source,
        body_patch,
        macros->body);

    /* Stage 2: EDGE */
    twilight1_edge_apply(
        body_patch,
        edge_patch,
        macros->edge);

    /* Stage 3: GROWL */
    twilight1_growl_apply(
        edge_patch,
        output,
        macros->growl);

    return 0;
}
