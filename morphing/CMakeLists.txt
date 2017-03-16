add_library(morphing
    morphing.cpp
)

target_link_libraries(morphing geom_helpers)

install(
    TARGETS morphing
    EXPORT morphing
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

export(
    EXPORT morphing
    FILE "${CMAKE_CURRENT_BINARY_DIR}/morphing-config.cmake"
)

install(
    EXPORT morphing
    FILE "morphing-config.cmake"
    DESTINATION "lib/cmake/morphing"
)
