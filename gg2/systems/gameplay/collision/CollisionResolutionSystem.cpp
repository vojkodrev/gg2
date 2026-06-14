#include "CollisionResolutionSystem.h"
#include "IsStatic.h"
#include "GetEntityColAABB.h"
#include "GetDynamicEntityPos.h"
#include "SetDynamicEntityPos.h"
#include <cmath>

void collisionResolutionSystem(Context &ctx)
{
    auto &cr = ctx.collision.collisions;

    for (uint32_t k = 0; k < cr.count; k++)
    {
        uint32_t idA = cr.pair.a[k];
        uint32_t idB = cr.pair.b[k];
        ColType typeA = colIdType(idA);
        ColType typeB = colIdType(idB);

        SDL_FRect a = getEntityColAABB(ctx, idA);
        SDL_FRect b = getEntityColAABB(ctx, idB);

        float overlapX = std::fminf(a.x + a.w, b.x + b.w) - std::fmaxf(a.x, b.x);
        float overlapY = std::fminf(a.y + a.h, b.y + b.h) - std::fmaxf(a.y, b.y);

        if (overlapX <= 0.0f || overlapY <= 0.0f)
            continue;

        bool staticA = isStatic(typeA);
        bool staticB = isStatic(typeB);

        float pushA = staticA ? 0.0f : (staticB ? 1.0f : 0.5f);
        float pushB = staticB ? 0.0f : (staticA ? 1.0f : 0.5f);

        SDL_FPoint posA = staticA ? SDL_FPoint{} : getDynamicEntityPos(ctx, idA);
        SDL_FPoint posB = staticB ? SDL_FPoint{} : getDynamicEntityPos(ctx, idB);

        if (overlapX < overlapY)
        {
            if (a.x < b.x)
            {
                posA.x -= overlapX * pushA;
                posB.x += overlapX * pushB;
            }
            else
            {
                posA.x += overlapX * pushA;
                posB.x -= overlapX * pushB;
            }
        }
        else
        {
            if (a.y < b.y)
            {
                posA.y -= overlapY * pushA;
                posB.y += overlapY * pushB;
            }
            else
            {
                posA.y += overlapY * pushA;
                posB.y -= overlapY * pushB;
            }
        }

        if (!staticA)
            setDynamicEntityPos(ctx, idA, posA);
        if (!staticB)
            setDynamicEntityPos(ctx, idB, posB);
    }
}
