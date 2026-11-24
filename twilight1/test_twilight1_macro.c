#include <assert.h>
#include <stdio.h>

#include "twilight1_macro.h"

int main(void)
{
    twilight1_macro_values_t macros;

    /* Test initialization */
    twilight1_macro_init(&macros);

    assert(macros.body == 0);
    assert(macros.edge == 0);
    assert(macros.growl == 0);
    assert(macros.motion == 0);
    assert(macros.space == 0);
    assert(macros.mutate == 0);

    /* Test setting a single macro */
    twilight1_macro_set(&macros, TWILIGHT_K1_BODY, 75);
    assert(macros.body == 75);
    assert(macros.edge == 0);

    /* Test lower boundary */
    twilight1_macro_set(&macros, TWILIGHT_K2_EDGE, -10);
    assert(macros.edge == 0);

    /* Test upper boundary */
    twilight1_macro_set(&macros, TWILIGHT_K3_GROWL, 150);
    assert(macros.growl == 100);

    /* Test independent macro values */
    twilight1_macro_set(&macros, TWILIGHT_K4_MOTION, 45);
    twilight1_macro_set(&macros, TWILIGHT_K5_SPACE, 30);
    twilight1_macro_set(&macros, TWILIGHT_K6_MUTATE, 90);

    assert(macros.body == 75);
    assert(macros.edge == 0);
    assert(macros.growl == 100);
    assert(macros.motion == 45);
    assert(macros.space == 30);
    assert(macros.mutate == 90);

    /* Test null safety */
    twilight1_macro_init(NULL);
    twilight1_macro_set(NULL, TWILIGHT_K1_BODY, 50);

    printf("TWILIGHT-1 macro tests passed!\n");

    return 0;
}
