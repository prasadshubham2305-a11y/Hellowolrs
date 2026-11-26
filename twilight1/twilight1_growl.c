#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156

static const uint8_t twilight_operator_levels[6] = {
    16, 37, 58, 79, 100, 121
};

/* Operator-specific GROWL intensity weights.
   GROWL shapes operators asymmetrically.
   Maximum nominal boost is 20% at full weight.
   Native operator level is capped at 99. */
static const uint8_t twilight_growl_weights[6] = {
    15, 40, 70, 100, 55, 25
};

void twilight1_growl_apply(
    const uint8_t source[TWILIGHT_FM_PATCH_BYTES],
    uint8_t output[TWILIGHT_FM_PATCH_BYTES],
    unsigned growl)
{
    if (!source || !output || growl > 100)
        return;

    memcpy(output, source, TWILIGHT_FM_PATCH_BYTES);

    if (growl == 0)
        return;

    for (unsigned i = 0; i < 6; i++) {
        unsigned offset = twilight_operator_levels[i];
        unsigned level = source[offset];

        unsigned boost =
            (level * growl * twilight_growl_weights[i]) / 50000;

        if (level + boost > 99)
            output[offset] = 99;
        else
            output[offset] = level + boost;
    }
}
