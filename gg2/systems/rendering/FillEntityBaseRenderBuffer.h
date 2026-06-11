#pragma once
#include "../../structs/core/EntityBase.h"
#include "../../structs/render/RenderBuffer.h"
#include <cstdint>

template<int N>
inline uint32_t fillEntityBaseRenderBuffer(
    RenderBuffer &rb,
    const EntityBase<N> &entityBase,
    uint32_t entityIndex,
    int groupId,
    int zIndex)
{
    int frameIndex = entityBase.animation.frameIndex[entityIndex];
    uint32_t renderIndex = rb.count++;

    rb.src.x[renderIndex] = (float)entityBase.animation.frame.src.x[entityIndex][frameIndex];
    rb.src.y[renderIndex] = (float)entityBase.animation.frame.src.y[entityIndex][frameIndex];
    rb.src.w[renderIndex] = (float)entityBase.animation.frame.src.w[entityIndex][frameIndex];
    rb.src.h[renderIndex] = (float)entityBase.animation.frame.src.h[entityIndex][frameIndex];
    rb.src.rotate[renderIndex] = 0.0f;
    rb.rotationCenter.point.x[renderIndex] = entityBase.rotation.center.point.x[entityIndex];
    rb.rotationCenter.point.y[renderIndex] = entityBase.rotation.center.point.y[entityIndex];
    rb.rotationCenter.hasCenter[renderIndex] = entityBase.rotation.center.hasCenter[entityIndex];

    rb.dst.x[renderIndex] = entityBase.position.x[entityIndex];
    rb.dst.y[renderIndex] = entityBase.position.y[entityIndex];
    rb.dst.w[renderIndex] = entityBase.position.w[entityIndex];
    rb.dst.h[renderIndex] = entityBase.position.h[entityIndex];
    rb.dst.depthY[renderIndex] = entityBase.depthY[entityIndex];

    rb.group.id[renderIndex] = groupId;
    rb.group.zIndex[renderIndex] = zIndex;
    rb.flipX[renderIndex] = entityBase.facing.flipX[entityIndex];

    return renderIndex;
}
