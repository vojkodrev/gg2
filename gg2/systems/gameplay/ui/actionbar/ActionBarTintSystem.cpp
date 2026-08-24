#include "ActionBarTintSystem.h"
#include "SetMagicActionBarIconsTint.h"
#include "SetRangedActionBarIconsTint.h"

void actionBarTintSystem(Context &ctx)
{
    setRangedActionBarIconsTint(ctx);
    setMagicActionBarIconsTint(ctx);
}
