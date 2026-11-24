#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156

static const uint8_t twilight_operator_levels[6] = {
    16, 37, 58, 79, 100, 121
};

/* BODY 0 is neutral. BODY 100 boosts operator output
   levels conservatively, capped at native DX7 level 99.
   Source patch remains untouched. */
void twilight1_body_apply(
    const uint8_t source[TWILIGHT_FM_PATCH_BYTES],
    uint8_t output[TWILIGHT_FM_PATCH_BYTES],
    unsigned body)
{
    if (!source || !output || body > 100)
        return;

    memcpy(output, source, TWILIGHT_FM_PATCH_BYTES);

    if (body == 0)
        return;

    for (unsigned i = 0; i < 6; i++) {
        unsigned offset = twilight_operator_levels[i];
        unsigned level = source[offset];
        unsigned boost = (level * body * 20) / 10000;

        if (level + boost > 99)
            output[offset] = 99;
        else
            output[offset] = level + boost;
    }
}
