add_library(systems_core
    frame/FrameRateLimitSystem.cpp
    frame/UpdateFrameStateSystem.cpp
    input/UpdateKeyboardStateSystem.cpp
    tilemap/FindLayer.cpp
    tilemap/GetCollision.cpp
    tilemap/GetTileProp.cpp
    tilemap/IsMarker.cpp
    tilemap/LoadGround.cpp
    tilemap/LoadNPCs.cpp
    tilemap/LoadObjects.cpp
    tilemap/LoadPlayer.cpp
    tilemap/LoadTileMap.cpp
)
target_include_directories(systems_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/frame
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    ${CMAKE_CURRENT_SOURCE_DIR}/tilemap
)
target_link_libraries(systems_core PUBLIC gg2_common tmxlite)
