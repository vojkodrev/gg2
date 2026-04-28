add_library(systems_rendering
    FillRenderBufferSystem.cpp
    FillPlayerRenderBuffer.cpp
    FillNpcRenderBuffer.cpp
    FillObjectRenderBuffer.cpp
    SortRenderBuffer.cpp
    RenderSystem.cpp
    DebugRenderSystem.cpp
)
target_include_directories(systems_rendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(systems_rendering PUBLIC gg2_common)
