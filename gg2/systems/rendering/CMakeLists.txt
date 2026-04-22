add_library(systems_rendering
    FillRenderBufferSystem.cpp
    FillPlayerRenderBuffer.cpp
    FillNpcRenderBuffer.cpp
    FillObjectRenderBuffer.cpp
    SortRenderBuffer.cpp
    RenderSystem.cpp
)
target_link_libraries(systems_rendering PUBLIC gg2_common)
