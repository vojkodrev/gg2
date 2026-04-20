add_subdirectory(systems/core/frame)
add_subdirectory(systems/core/input)
add_subdirectory(systems/core/tilemap)
add_subdirectory(systems/rendering)
add_subdirectory(systems/gameplay)

add_executable(gg2 gg2.cpp)

target_include_directories(gg2 PRIVATE
    structs/core
    structs/tilemap
    structs/npc
    structs/object
    structs/render
    structs/player
    ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/include
    ${CMAKE_SOURCE_DIR}/vendor/SDL3_image-3.4.2/include
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/vendor/tmxlite/tmxlite/include
)

target_link_libraries(gg2 PRIVATE
    systems_frame
    systems_input
    systems_tilemap
    systems_rendering
    systems_gameplay
    ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/lib/x64/SDL3.lib
    ${CMAKE_SOURCE_DIR}/vendor/SDL3_image-3.4.2/lib/x64/SDL3_image.lib
)
