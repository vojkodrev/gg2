add_library(systems_rendering
    FillActionBarRenderBuffer.cpp
    FillRenderBufferSystem.cpp
    FillPlayerRenderBuffer.cpp
    FillNpcRenderBuffer.cpp
    FillObjectRenderBuffer.cpp
    FillEffectRenderBuffer.cpp
    SortRenderBuffer.cpp
    RenderSystem.cpp
    debug/DebugRenderSystem.cpp
    debug/DebugRenderPlayer.cpp
    debug/DebugRenderNpc.cpp
    debug/DebugRenderObjects.cpp
    debug/DebugRenderEffect.cpp
    debug/DebugRenderAstar.cpp
    debug/DebugRenderRangedDeadZone.cpp
)
target_include_directories(systems_rendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(systems_rendering PUBLIC gg2_common)
