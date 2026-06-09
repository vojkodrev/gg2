add_library(systems_core
    frame/FrameRateLimitSystem.cpp
    frame/RefreshFrameTiming.cpp
    input/ActionStateSystem.cpp
    input/DebugStateSystem.cpp
    input/KeyboardStateSystem.cpp
    input/MouseStateSystem.cpp
)
target_include_directories(systems_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/frame
    ${CMAKE_CURRENT_SOURCE_DIR}/input
)
target_link_libraries(systems_core PUBLIC gg2_common)
