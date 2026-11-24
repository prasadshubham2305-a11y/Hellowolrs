#include "twilight1_macro.h"

void twilight1_macro_init(twilight1_macro_values_t *macros)
{
    if (!macros)
        return;

    macros->body   = 0;
    macros->edge   = 0;
    macros->growl  = 0;
    macros->motion = 0;
    macros->space  = 0;
    macros->mutate = 0;
}

void twilight1_macro_set(
    twilight1_macro_values_t *macros,
    twilight1_macro_id_t id,
    int value)
{
    if (!macros)
        return;

    uint8_t v = twilight1_macro_clamp(value);

    switch (id) {
    case TWILIGHT_K1_BODY:
        macros->body = v;
        break;

    case TWILIGHT_K2_EDGE:
        macros->edge = v;
        break;

    case TWILIGHT_K3_GROWL:
        macros->growl = v;
        break;

    case TWILIGHT_K4_MOTION:
        macros->motion = v;
        break;

    case TWILIGHT_K5_SPACE:
        macros->space = v;
        break;

    case TWILIGHT_K6_MUTATE:
        macros->mutate = v;
        break;

    default:
        break;
    }
}
