#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/render/RenderBuffer.h"
#include <cstdint>

template<int N>
inline void fillEquipmentEntityRenderBuffer(
    RenderBuffer &rb,
    const EntityBase<N> &entityBase,
    uint32_t parentEntityIndex,
    uint32_t parentRenderIndex,
    uint32_t groupId,
    int zIndex)
{
    const auto &animation = entityBase.animation;
    if (animation.frameCount[parentEntityIndex] == 0)
        return;

    int ef = animation.frameIndex[parentEntityIndex];
    uint32_t en = rb.count++;

    rb.src.x[en] = (float)animation.frame.src.x[parentEntityIndex][ef];
    rb.src.y[en] = (float)animation.frame.src.y[parentEntityIndex][ef];
    rb.src.w[en] = (float)animation.frame.src.w[parentEntityIndex][ef];
    rb.src.h[en] = (float)animation.frame.src.h[parentEntityIndex][ef];

    rb.group.id[en] = groupId;
    rb.group.zIndex[en] = zIndex;
    rb.flipX[en] = entityBase.facing.flipX[parentEntityIndex];

    rb.dst.w[en] = entityBase.position.w[parentEntityIndex];
    rb.dst.h[en] = entityBase.position.h[parentEntityIndex];
    rb.dst.x[en] = entityBase.position.x[parentEntityIndex];
    rb.dst.y[en] = entityBase.position.y[parentEntityIndex];
    rb.dst.depthY[en] = entityBase.depthY[parentEntityIndex];

    rb.src.rotate[en] = entityBase.rotation.rotate[parentEntityIndex];
    rb.rotationCenter.point.x[en] = entityBase.rotation.center.point.x[parentEntityIndex];
    rb.rotationCenter.point.y[en] = entityBase.rotation.center.point.y[parentEntityIndex];
    rb.rotationCenter.hasCenter[en] = entityBase.rotation.center.hasCenter[parentEntityIndex];
}
