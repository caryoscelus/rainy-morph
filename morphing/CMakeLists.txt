add_library(morphing
    morphing.cpp
)

target_include_directories(morphing
    SYSTEM BEFORE PUBLIC
        ${LIB2GEOM_INCLUDE_DIRS}
)
target_link_libraries(morphing ${LIB2GEOM_LIBRARIES})

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
