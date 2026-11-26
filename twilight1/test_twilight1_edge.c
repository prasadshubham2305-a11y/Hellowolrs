#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TWILIGHT_FM_PATCH_BYTES 156
#define TWILIGHT_FEEDBACK_OFFSET 135

void twilight1_edge_apply(
    const uint8_t source[TWILIGHT_FM_PATCH_BYTES],
    uint8_t output[TWILIGHT_FM_PATCH_BYTES],
    unsigned edge
);

static void test_edge_neutral(void)
{
    uint8_t source[TWILIGHT_FM_PATCH_BYTES] = {0};
    uint8_t output[TWILIGHT_FM_PATCH_BYTES];

    source[TWILIGHT_FEEDBACK_OFFSET] = 1;

    twilight1_edge_apply(source, output, 0);

    assert(output[TWILIGHT_FEEDBACK_OFFSET] == 1);
    assert(memcmp(source, output, TWILIGHT_FM_PATCH_BYTES) == 0);
}

static void test_edge_levels(void)
{
    unsigned levels[] = {25, 50, 75, 100};
    uint8_t expected[] = {2, 3, 4, 5};

    for (unsigned i = 0; i < 4; i++) {
        uint8_t source[TWILIGHT_FM_PATCH_BYTES] = {0};
        uint8_t output[TWILIGHT_FM_PATCH_BYTES];

        source[TWILIGHT_FEEDBACK_OFFSET] = 1;

        twilight1_edge_apply(source, output, levels[i]);

        assert(output[TWILIGHT_FEEDBACK_OFFSET] == expected[i]);
    }
}

static void test_edge_cap(void)
{
    uint8_t source[TWILIGHT_FM_PATCH_BYTES] = {0};
    uint8_t output[TWILIGHT_FM_PATCH_BYTES];

    source[TWILIGHT_FEEDBACK_OFFSET] = 6;

    twilight1_edge_apply(source, output, 100);

    assert(output[TWILIGHT_FEEDBACK_OFFSET] == 7);
}

static void test_source_unchanged(void)
{
    uint8_t source[TWILIGHT_FM_PATCH_BYTES] = {0};
    uint8_t original[TWILIGHT_FM_PATCH_BYTES];
    uint8_t output[TWILIGHT_FM_PATCH_BYTES];

    source[TWILIGHT_FEEDBACK_OFFSET] = 2;
    memcpy(original, source, TWILIGHT_FM_PATCH_BYTES);

    twilight1_edge_apply(source, output, 100);

    assert(memcmp(source, original, TWILIGHT_FM_PATCH_BYTES) == 0);
}

static void test_unrelated_bytes(void)
{
    uint8_t source[TWILIGHT_FM_PATCH_BYTES] = {0};
    uint8_t output[TWILIGHT_FM_PATCH_BYTES];

    source[10] = 55;
    source[80] = 23;
    source[TWILIGHT_FEEDBACK_OFFSET] = 1;

    twilight1_edge_apply(source, output, 100);

    assert(output[10] == 55);
    assert(output[80] == 23);
}

int main(void)
{
    test_edge_neutral();
    test_edge_levels();
    test_edge_cap();
    test_source_unchanged();
    test_unrelated_bytes();

    printf("TWILIGHT-1 EDGE tests passed\n");
    return 0;
}
