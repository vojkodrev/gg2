add_library(systems_frame
    FrameRateLimitSystem.cpp
    UpdateFrameStateSystem.cpp
)

target_include_directories(systems_frame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/gg2/structs/core
    ${CMAKE_SOURCE_DIR}/gg2/structs/tilemap
    ${CMAKE_SOURCE_DIR}/gg2/structs/npc
    ${CMAKE_SOURCE_DIR}/gg2/structs/object
    ${CMAKE_SOURCE_DIR}/gg2/structs/render
    ${CMAKE_SOURCE_DIR}/gg2/structs/player
    ${CMAKE_SOURCE_DIR}/gg2/structs/collision
    ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/include
)
