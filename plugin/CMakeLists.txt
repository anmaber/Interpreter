add_library(
    Interp4Move SHARED
    inc/Interp4Move.hh
    src/Interp4Move.cpp
)

add_library(
    Interp4Set SHARED
    inc/Interp4Set.hh
    src/Interp4Set.cpp
)

add_library(
    Interp4Pause SHARED
    inc/Interp4Pause.hh
    src/Interp4Pause.cpp
)

add_library(
    Interp4Rotate SHARED
    inc/Interp4Rotate.hh
    src/Interp4Rotate.cpp
)

target_include_directories(Interp4Move PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc" "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
target_include_directories(Interp4Set PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc" "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
target_include_directories(Interp4Pause PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc" "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
target_include_directories(Interp4Rotate PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc" "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
