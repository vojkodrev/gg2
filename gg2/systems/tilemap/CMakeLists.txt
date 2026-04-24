add_library(systems_tilemap
    FindLayer.cpp
    GetCollision.cpp
    GetTileProp.cpp
    IsMarker.cpp
    LoadGround.cpp
    LoadNPCs.cpp
    LoadObjects.cpp
    LoadPlayer.cpp
    LoadTileMap.cpp
)
target_include_directories(systems_tilemap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(systems_tilemap PUBLIC gg2_common tmxlite)
