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
    rb.src.rotate[renderIndex] = entityBase.rotation.rotate[entityIndex];
    rb.rotationCenter.point.x[renderIndex][0] = entityBase.rotation.center.point.x[entityIndex][0];
    rb.rotationCenter.point.y[renderIndex][0] = entityBase.rotation.center.point.y[entityIndex][0];
    rb.rotationCenter.hasCenter[renderIndex] = entityBase.rotation.center.hasCenter[entityIndex];

    rb.dst.x[renderIndex] = entityBase.position.x[entityIndex];
    rb.dst.y[renderIndex] = entityBase.position.y[entityIndex];
    rb.dst.w[renderIndex] = entityBase.position.w[entityIndex];
    rb.dst.h[renderIndex] = entityBase.position.h[entityIndex];
    rb.dst.depthY[renderIndex] = entityBase.depthY[entityIndex];
    rb.dst.absolute[renderIndex] = entityBase.position.absolute[entityIndex];

    rb.group.id[renderIndex] = groupId;
    rb.group.zIndex[renderIndex] = zIndex;
    rb.flipX[renderIndex] = entityBase.facing.flipX[entityIndex];
    rb.tint.r[renderIndex] = entityBase.tint.r[entityIndex];
    rb.tint.g[renderIndex] = entityBase.tint.g[entityIndex];
    rb.tint.b[renderIndex] = entityBase.tint.b[entityIndex];
    rb.tint.a[renderIndex] = entityBase.tint.a[entityIndex];

    return renderIndex;
}
