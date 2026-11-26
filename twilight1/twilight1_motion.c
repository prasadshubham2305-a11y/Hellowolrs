#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156
#define TWILIGHT_PMD_OFFSET 139
#define TWILIGHT_AMD_OFFSET 140
#define TWILIGHT_PMS_OFFSET 143
#define TWILIGHT_OP_BYTES 21
#define TWILIGHT_OP_AMSENS 14
#define TWILIGHT_OP_LEVEL 16
#define TWILIGHT_OPS 6
#define TWILIGHT_PMS_FLOOR 3

/* MOTION adds vibrato and tremolo depth without changing the
   character of the patch. Depth values are only raised, never
   lowered, and every enabler sensitivity is set so the movement
   is actually audible. Source patch remains untouched. */
void twilight1_motion_apply(
    const uint8_t source[TWILIGHT_FM_PATCH_BYTES],
    uint8_t output[TWILIGHT_FM_PATCH_BYTES],
    unsigned motion)
{
    if (!source || !output || motion > 100)
        return;

    memcpy(output, source, TWILIGHT_FM_PATCH_BYTES);

    if (motion == 0)
        return;

    unsigned pmd = (motion * 60) / 100;
    unsigned amd = (motion * 40) / 100;

    if ((unsigned)source[TWILIGHT_PMD_OFFSET] > pmd)
        pmd = source[TWILIGHT_PMD_OFFSET];

    if ((unsigned)source[TWILIGHT_AMD_OFFSET] > amd)
        amd = source[TWILIGHT_AMD_OFFSET];

    output[TWILIGHT_PMD_OFFSET] = (uint8_t)pmd;
    output[TWILIGHT_AMD_OFFSET] = (uint8_t)amd;

    if (pmd > 0 && (source[TWILIGHT_PMS_OFFSET] & 7) == 0)
        output[TWILIGHT_PMS_OFFSET] = TWILIGHT_PMS_FLOOR;

    if (amd > 0) {
        for (unsigned op = 0; op < TWILIGHT_OPS; op++) {
            unsigned base = op * TWILIGHT_OP_BYTES;

            if ((source[base + TWILIGHT_OP_AMSENS] & 3) == 0 &&
                source[base + TWILIGHT_OP_LEVEL] > 0)
                output[base + TWILIGHT_OP_AMSENS] = 1;
        }
    }
}
