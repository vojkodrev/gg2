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
    ${CMAKE_SOURCE_DIR}/gg2/structs/core
    ${CMAKE_SOURCE_DIR}/gg2/structs/tilemap
    ${CMAKE_SOURCE_DIR}/gg2/structs/npc
    ${CMAKE_SOURCE_DIR}/gg2/structs/object
    ${CMAKE_SOURCE_DIR}/gg2/structs/render
    ${CMAKE_SOURCE_DIR}/gg2/structs/player
    ${CMAKE_SOURCE_DIR}/gg2/structs/collision
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/include
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/include
)

add_library(tmxlite STATIC
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/FreeFuncs.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/ImageLayer.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/LayerGroup.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/Map.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/Object.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/ObjectGroup.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/ObjectTypes.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/Property.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/TileLayer.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/Tileset.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/detail/pugixml.cpp
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/src/miniz.c
)

target_include_directories(tmxlite PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/include
    ${CMAKE_SOURCE_DIR}/vendor
)

target_link_libraries(systems_tilemap PUBLIC tmxlite)
