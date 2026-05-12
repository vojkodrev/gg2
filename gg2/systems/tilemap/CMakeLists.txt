add_library(systems_tilemap
    FindLayer.cpp
    GetCollision.cpp
    IsMarker.cpp
    LoadGround.cpp
    LoadNPCs.cpp
    LoadObjects.cpp
    LoadPlayer.cpp
    LoadTileMap.cpp
    properties/FindTileByType.cpp
    properties/GetTileFloatProp.cpp
    properties/GetTilePropInt.cpp
    properties/GetTileStringProp.cpp
)
target_include_directories(systems_tilemap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(systems_tilemap PUBLIC gg2_common tmxlite)
