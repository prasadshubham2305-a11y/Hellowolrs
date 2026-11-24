#include <stdint.h>

#include "twilight1_macro.h"

#define TWILIGHT1_PATCH_BYTES 156

/* BODY transformation implemented in twilight1_body.c */
void twilight1_body_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    unsigned body);

/* TWILIGHT-1 Engine Core v1
   Original patch is never modified.
   Transformations are applied to a separate output buffer.
*/
int twilight1_engine_apply(
    const uint8_t source[TWILIGHT1_PATCH_BYTES],
    uint8_t output[TWILIGHT1_PATCH_BYTES],
    const twilight1_macro_values_t *macros)
{
    if (!source || !output || !macros)
        return -1;

    /* K1 BODY only in Engine Core v1 */
    twilight1_body_apply(
        source,
        output,
        macros->body);

    return 0;
}
