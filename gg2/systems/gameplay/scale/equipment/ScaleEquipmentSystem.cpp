#include "ScaleEquipmentSystem.h"
#include "ScaleAmmo.h"
#include "ScaleWeapon.h"

void scaleEquipmentSystem(Context &ctx)
{
    scaleAmmo(ctx);
    scaleWeapon(ctx);
}
