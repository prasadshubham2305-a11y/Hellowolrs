#include <assert.h>
#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156

void twilight1_body_apply(
    const uint8_t source[156],
    uint8_t output[156],
    unsigned body);

int main(void)
{
    uint8_t source[156] = {0};
    uint8_t output[156];
    uint8_t original[156];

    const unsigned offsets[6] = {16, 37, 58, 79, 100, 121};

    for (unsigned i = 0; i < 6; i++)
        source[offsets[i]] = 80;

    memcpy(original, source, 156);

    /* BODY zero: unchanged patch */
    twilight1_body_apply(source, output, 0);
    assert(memcmp(source, output, 156) == 0);

    /* BODY maximum: conservative boost */
    twilight1_body_apply(source, output, 100);

    for (unsigned i = 0; i < 6; i++)
        assert(output[offsets[i]] <= 99);

    /* Source must remain untouched */
    assert(memcmp(source, original, 156) == 0);

    return 0;
}
