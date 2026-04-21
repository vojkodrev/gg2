add_subdirectory(systems/core/frame)
add_subdirectory(systems/core/input)
add_subdirectory(systems/core/tilemap)
add_subdirectory(systems/rendering)
add_subdirectory(systems/gameplay)

add_executable(gg2 main.cpp)

target_include_directories(gg2 PRIVATE
    structs/core
    structs/tilemap
    structs/npc
    structs/object
    structs/render
    structs/player
    structs/collision
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

add_custom_command(TARGET gg2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/lib/x64/SDL3.dll
        ${CMAKE_SOURCE_DIR}/vendor/SDL3_image-3.4.2/lib/x64/SDL3_image.dll
        $<TARGET_FILE_DIR:gg2>
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:gg2>/assets/map
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:gg2>/assets/texture
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/map/map1.tmx
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/map/texture.tsx
        $<TARGET_FILE_DIR:gg2>/assets/map
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/texture/texture.png
        $<TARGET_FILE_DIR:gg2>/assets/texture
)
