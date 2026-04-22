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
)
target_link_libraries(systems_gameplay PUBLIC gg2_common)
