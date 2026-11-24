
#include <assert.h>
#include <stdint.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156

void twilight1_body_apply(
    const uint8_t source[156],
    uint8_t output[156],
    unsigned body);

static const unsigned offsets[6] = {16, 37, 58, 79, 100, 121};

int main(void)
{
    uint8_t source[156] = {0};
    uint8_t output[156];
    uint8_t original[156];

    for (unsigned i = 0; i < 6; i++)
        source[offsets[i]] = 80;

    memcpy(original, source, sizeof source);

    /* BODY zero: neutral */
    twilight1_body_apply(source, output, 0);
    assert(memcmp(source, output, sizeof source) == 0);

    /* BODY 50: expected 10 percent boost */
    twilight1_body_apply(source, output, 50);
    for (unsigned i = 0; i < 6; i++)
        assert(output[offsets[i]] == 88);

    /* BODY 100: expected 20 percent boost */
    twilight1_body_apply(source, output, 100);
    for (unsigned i = 0; i < 6; i++)
        assert(output[offsets[i]] == 96);

    /* Source patch remains untouched */
    assert(memcmp(source, original, sizeof source) == 0);

    /* Level ceiling: 99 */
    memset(source, 0, sizeof source);
    source[offsets[0]] = 99;
    source[offsets[1]] = 95;

    twilight1_body_apply(source, output, 100);
    assert(output[offsets[0]] == 99);
    assert(output[offsets[1]] == 99);

    /* Other patch bytes remain unchanged */
    source[0] = 42;
    source[155] = 77;

    twilight1_body_apply(source, output, 100);
    assert(output[0] == 42);
    assert(output[155] == 77);

    /* Invalid BODY must not overwrite output */
    memset(output, 0xA5, sizeof output);
    twilight1_body_apply(source, output, 101);

    for (unsigned i = 0; i < sizeof output; i++)
        assert(output[i] == 0xA5);

    return 0;
}
