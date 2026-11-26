#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PATCH_BYTES 156

void twilight1_motion_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    unsigned motion);

static void test_neutral(void)
{
    uint8_t source[PATCH_BYTES];
    uint8_t output[PATCH_BYTES];

    for (unsigned i = 0; i < PATCH_BYTES; i++)
        source[i] = (uint8_t)(i % 128);

    twilight1_motion_apply(source, output, 0);

    assert(memcmp(source, output, PATCH_BYTES) == 0);
}

static void test_depth_scaling(void)
{
    const unsigned levels[3] = { 25, 50, 100 };
    const uint8_t expected_pmd[3] = { 15, 30, 60 };
    const uint8_t expected_amd[3] = { 10, 20, 40 };

    for (unsigned i = 0; i < 3; i++) {
        uint8_t source[PATCH_BYTES] = {0};
        uint8_t output[PATCH_BYTES];

        twilight1_motion_apply(source, output, levels[i]);

        assert(output[139] == expected_pmd[i]);
        assert(output[140] == expected_amd[i]);
        assert(output[143] == 3);
        assert(source[139] == 0);
        assert(source[140] == 0);
    }
}

static void test_existing_depth_preserved(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    source[139] = 90;
    source[140] = 80;

    twilight1_motion_apply(source, output, 50);

    assert(output[139] == 90);
    assert(output[140] == 80);
}

static void test_pms_floor(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    source[143] = 0;
    twilight1_motion_apply(source, output, 100);
    assert(output[143] == 3);

    source[143] = 5;
    twilight1_motion_apply(source, output, 100);
    assert(output[143] == 5);
}

static void test_amp_mod_sensitivity(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    for (unsigned op = 0; op < 6; op++)
        source[op * 21 + 16] = 50;

    /* Operator 2 has no output level: it must stay silent. */
    source[2 * 21 + 16] = 0;

    twilight1_motion_apply(source, output, 100);

    for (unsigned op = 0; op < 6; op++) {
        unsigned sens = output[op * 21 + 14];

        if (op == 2)
            assert(sens == 0);
        else
            assert(sens == 1);
    }
}

static void test_unrelated_bytes(void)
{
    uint8_t source[PATCH_BYTES];
    uint8_t output[PATCH_BYTES];

    for (unsigned i = 0; i < PATCH_BYTES; i++)
        source[i] = (uint8_t)(i % 100);

    for (unsigned op = 0; op < 6; op++)
        source[op * 21 + 16] = 50;

    source[139] = 0;
    source[140] = 0;
    source[143] = 0;

    twilight1_motion_apply(source, output, 100);

    for (unsigned i = 0; i < PATCH_BYTES; i++) {
        if (i == 139 || i == 140 || i == 143)
            continue;

        if (i < 126 && (i % 21) == 14)
            continue;

        assert(output[i] == source[i]);
    }
}

static void test_invalid_range(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    memset(output, 0xA5, PATCH_BYTES);
    twilight1_motion_apply(source, output, 101);

    for (unsigned i = 0; i < PATCH_BYTES; i++)
        assert(output[i] == 0xA5);
}

int main(void)
{
    test_neutral();
    test_depth_scaling();
    test_existing_depth_preserved();
    test_pms_floor();
    test_amp_mod_sensitivity();
    test_unrelated_bytes();
    test_invalid_range();

    printf("TWILIGHT-1 MOTION tests passed\n");
    return 0;
}
