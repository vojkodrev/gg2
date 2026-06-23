if(WIN32)
    set(CMAKE_PREFIX_PATH
        "${CMAKE_SOURCE_DIR}/vendor/SDL3-3.4.4/cmake"
        "${CMAKE_SOURCE_DIR}/vendor/SDL3_image-3.4.2/cmake"
    )
endif()

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_library(gg2_common INTERFACE)
target_link_libraries(gg2_common INTERFACE SDL3::SDL3 SDL3_image::SDL3_image)
target_include_directories(gg2_common INTERFACE
    ${CMAKE_SOURCE_DIR}/gg2/structs/core
    ${CMAKE_SOURCE_DIR}/gg2/structs/core/constants
    ${CMAKE_SOURCE_DIR}/gg2/structs/tilemap
    ${CMAKE_SOURCE_DIR}/gg2/structs/npc
    ${CMAKE_SOURCE_DIR}/gg2/structs/object
    ${CMAKE_SOURCE_DIR}/gg2/structs/effect
    ${CMAKE_SOURCE_DIR}/gg2/structs/render
    ${CMAKE_SOURCE_DIR}/gg2/structs/player
    ${CMAKE_SOURCE_DIR}/gg2/structs/collision
    ${CMAKE_SOURCE_DIR}/gg2/utils/collision
    ${CMAKE_SOURCE_DIR}/gg2/utils/minheap
    ${CMAKE_SOURCE_DIR}/gg2/utils/timers
    ${CMAKE_SOURCE_DIR}/gg2/utils/queue
    ${CMAKE_SOURCE_DIR}/gg2/utils/sort
    ${CMAKE_SOURCE_DIR}/gg2/utils/grid
)

include(cmake/tmxlite.cmake)

add_subdirectory(systems/core)
add_subdirectory(systems/tilemap)
add_subdirectory(systems/rendering)
add_subdirectory(systems/gameplay)

add_executable(gg2 main.cpp)
target_link_libraries(gg2 PRIVATE
    gg2_common
    systems_core
    systems_tilemap
    systems_rendering
    systems_gameplay
    SDL3::SDL3
    SDL3_image::SDL3_image
)

if(WIN32)
    add_custom_command(TARGET gg2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE:SDL3_image::SDL3_image>
            $<TARGET_FILE_DIR:gg2>
    )
endif()

add_custom_target(gg2_assets ALL
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

add_dependencies(gg2 gg2_assets)
