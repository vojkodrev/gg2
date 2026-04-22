add_library(systems_gameplay
    PlayerMovementSystem.cpp
    ai/NPCAiSystem.cpp
    ai/UpdateMonster.cpp
    ai/Dist.cpp
    ai/DistToPlayer.cpp
    ai/DistToSpawn.cpp
    ai/IsNearColEdge.cpp
    ai/MoveColCenterToward.cpp
    collision/CollisionSystem.cpp
    collision/CollisionResolutionSystem.cpp
)

target_include_directories(systems_gameplay PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ai
    ${CMAKE_CURRENT_SOURCE_DIR}/collision
    ${CMAKE_SOURCE_DIR}/gg2/structs/core
    ${CMAKE_SOURCE_DIR}/gg2/structs/tilemap
    ${CMAKE_SOURCE_DIR}/gg2/structs/npc
    ${CMAKE_SOURCE_DIR}/gg2/structs/object
    ${CMAKE_SOURCE_DIR}/gg2/structs/render
    ${CMAKE_SOURCE_DIR}/gg2/structs/player
    ${CMAKE_SOURCE_DIR}/gg2/structs/collision
    ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/include
)
