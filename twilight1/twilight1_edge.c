
#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156
#define TWILIGHT_FEEDBACK_OFFSET 135
#define TWILIGHT_FEEDBACK_MAX 7

void twilight1_edge_apply(
    const uint8_t source[TWILIGHT_FM_PATCH_BYTES],
    uint8_t output[TWILIGHT_FM_PATCH_BYTES],
    unsigned edge)
{
    if (!source || !output || edge > 100)
        return;

    memcpy(output, source, TWILIGHT_FM_PATCH_BYTES);

    if (edge == 0)
        return;

    unsigned original = source[TWILIGHT_FEEDBACK_OFFSET];

    /* EDGE adds a bounded feedback boost. */
    unsigned boost = (edge * 4 + 99) / 100;

    unsigned value = original + boost;

    if (value > TWILIGHT_FEEDBACK_MAX)
        value = TWILIGHT_FEEDBACK_MAX;

    output[TWILIGHT_FEEDBACK_OFFSET] = (uint8_t)value;
}
