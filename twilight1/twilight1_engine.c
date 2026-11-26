#include <stdint.h>
#include <string.h>

#include "twilight1_macro.h"

#define PATCH_BYTES 156

void twilight1_body_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    unsigned body);

void twilight1_edge_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    unsigned edge);

void twilight1_growl_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    unsigned growl);

int twilight1_engine_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    const twilight1_macro_values_t *macros)
{
    if (!source || !output || !macros)
        return -1;

    if (macros->body > 100 ||
        macros->edge > 100 ||
        macros->growl > 100 ||
        macros->motion > 100 ||
        macros->space > 100 ||
        macros->mutate > 100)
        return -1;

    uint8_t stage_a[PATCH_BYTES];
    uint8_t stage_b[PATCH_BYTES];

    /* SOURCE -> BODY */
    twilight1_body_apply(
        source, stage_a, macros->body);

    /* BODY -> EDGE */
    twilight1_edge_apply(
        stage_a, stage_b, macros->edge);

    /* EDGE -> GROWL */
    twilight1_growl_apply(
        stage_b, stage_a, macros->growl);

    /* Final output */
    memcpy(output, stage_a, PATCH_BYTES);

    return 0;
}
