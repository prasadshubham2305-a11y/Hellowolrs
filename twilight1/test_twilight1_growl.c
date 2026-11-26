#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PATCH_BYTES 156

static const uint8_t LEVEL_OFFSETS[6] = {
    16, 37, 58, 79, 100, 121
};

void twilight1_growl_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    unsigned growl
);

static void test_neutral(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    for (unsigned i = 0; i < 6; i++)
        source[LEVEL_OFFSETS[i]] = 50;

    twilight1_growl_apply(source, output, 0);

    assert(memcmp(source, output, PATCH_BYTES) == 0);
}

static void test_full_growl(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    uint8_t expected[6] = {
    51, 52, 53, 55, 52, 51
};

    for (unsigned i = 0; i < 6; i++)
        source[LEVEL_OFFSETS[i]] = 50;

    twilight1_growl_apply(source, output, 100);

    for (unsigned i = 0; i < 6; i++)
        assert(output[LEVEL_OFFSETS[i]] == expected[i]);
}

static void test_level_cap(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    for (unsigned i = 0; i < 6; i++)
        source[LEVEL_OFFSETS[i]] = 98;

    twilight1_growl_apply(source, output, 100);

    for (unsigned i = 0; i < 6; i++)
        assert(output[LEVEL_OFFSETS[i]] <= 99);
}

static void test_source_unchanged(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t original[PATCH_BYTES];
    uint8_t output[PATCH_BYTES];

    for (unsigned i = 0; i < 6; i++)
        source[LEVEL_OFFSETS[i]] = 50;

    memcpy(original, source, PATCH_BYTES);

    twilight1_growl_apply(source, output, 100);

    assert(memcmp(source, original, PATCH_BYTES) == 0);
}

static void test_unrelated_bytes(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];

    source[10] = 45;
    source[80] = 77;

    for (unsigned i = 0; i < 6; i++)
        source[LEVEL_OFFSETS[i]] = 50;

    twilight1_growl_apply(source, output, 100);

    assert(output[10] == 45);
    assert(output[80] == 77);
}

int main(void)
{
    test_neutral();
    test_full_growl();
    test_level_cap();
    test_source_unchanged();
    test_unrelated_bytes();

    printf("TWILIGHT-1 GROWL tests passed\n");
    return 0;
}
