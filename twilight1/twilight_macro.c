#include "twilight_macro.h"

void twilight_macros_init(twilight_macros_t *macros)
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
