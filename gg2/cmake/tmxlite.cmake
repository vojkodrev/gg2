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
