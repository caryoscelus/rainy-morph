add_library(geom_helpers SHARED
    compare.cpp
    knots.cpp
    split.cpp
)

target_include_directories(geom_helpers
    SYSTEM BEFORE PUBLIC
        ${LIB2GEOM_INCLUDE_DIRS}
)
target_link_libraries(geom_helpers ${LIB2GEOM_LIBRARIES})

install(
    TARGETS geom_helpers
    EXPORT geom_helpers
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

export(
    EXPORT geom_helpers
    FILE "${CMAKE_CURRENT_BINARY_DIR}/geom_helpers-config.cmake"
)

install(
    EXPORT geom_helpers
    FILE "geom_helpers-config.cmake"
    DESTINATION "lib/cmake/geom_helpers"
)
