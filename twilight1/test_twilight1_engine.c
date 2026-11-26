#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "twilight1_macro.h"

#define PATCH_BYTES 156
#define FEEDBACK_OFFSET 135

int twilight1_engine_apply(
    const uint8_t source[PATCH_BYTES],
    uint8_t output[PATCH_BYTES],
    const twilight1_macro_values_t *macros);

static void test_neutral(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];
    twilight1_macro_values_t macros;

    for (unsigned i = 0; i < 6; i++)
        source[16 + (i * 21)] = 80;

    twilight1_macro_init(&macros);

    assert(twilight1_engine_apply(source, output, &macros) == 0);
    assert(memcmp(source, output, PATCH_BYTES) == 0);
}

static void test_body_growl_chain(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];
    uint8_t original[PATCH_BYTES];
    twilight1_macro_values_t macros;

    const unsigned offsets[6] = {
        16, 37, 58, 79, 100, 121
    };

    const uint8_t expected[6] = {
        90, 95, 99, 99, 97, 92
    };

    for (unsigned i = 0; i < 6; i++)
        source[offsets[i]] = 80;

    memcpy(original, source, PATCH_BYTES);

    twilight1_macro_init(&macros);
    macros.body = 50;
    macros.growl = 100;

    assert(twilight1_engine_apply(source, output, &macros) == 0);

    for (unsigned i = 0; i < 6; i++)
        assert(output[offsets[i]] == expected[i]);

    assert(memcmp(source, original, PATCH_BYTES) == 0);
}

static void test_edge_in_engine(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];
    twilight1_macro_values_t macros;

    source[FEEDBACK_OFFSET] = 1;

    twilight1_macro_init(&macros);
    macros.edge = 50;

    assert(twilight1_engine_apply(source, output, &macros) == 0);

    assert(output[FEEDBACK_OFFSET] == 3);
    assert(source[FEEDBACK_OFFSET] == 1);
}

static void test_invalid_pointers(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];
    twilight1_macro_values_t macros;

    twilight1_macro_init(&macros);

    assert(twilight1_engine_apply(NULL, output, &macros) == -1);
    assert(twilight1_engine_apply(source, NULL, &macros) == -1);
    assert(twilight1_engine_apply(source, output, NULL) == -1);
}
static void test_invalid_macro_range(void)
{
    uint8_t source[PATCH_BYTES] = {0};
    uint8_t output[PATCH_BYTES];
    twilight1_macro_values_t macros;

    twilight1_macro_init(&macros);
    macros.body = 101;

    assert(twilight1_engine_apply(source, output, &macros) == -1);

    twilight1_macro_init(&macros);
    macros.edge = 101;

    assert(twilight1_engine_apply(source, output, &macros) == -1);

    twilight1_macro_init(&macros);
    macros.growl = 101;

    assert(twilight1_engine_apply(source, output, &macros) == -1);
}

static void test_untouched_bytes_preserved(void)
{
    uint8_t source[PATCH_BYTES];
    uint8_t output[PATCH_BYTES];
    twilight1_macro_values_t macros;

    for (unsigned i = 0; i < PATCH_BYTES; i++)
        source[i] = (uint8_t)(i % 128);

    twilight1_macro_init(&macros);
    macros.body = 50;
    macros.edge = 50;
    macros.growl = 50;

    assert(twilight1_engine_apply(source, output, &macros) == 0);

    /* Non-transformed bytes must remain unchanged. */
    for (unsigned i = 0; i < PATCH_BYTES; i++)
    {
        if (i == 16 || i == 37 || i == 58 ||
            i == 79 || i == 100 || i == 121 ||
            i == 135)
            continue;

        assert(output[i] == source[i]);
    }
}
int main(void)
{
    test_neutral();
    test_body_growl_chain();
    test_edge_in_engine();
    test_invalid_pointers();
test_invalid_macro_range();
    test_untouched_bytes_preserved();
    printf("TWILIGHT-1 Engine tests passed!\n");
    return 0;
}
