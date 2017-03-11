add_library(geom_helpers
    compare.cpp
    knots.cpp
    split.cpp
)

target_include_directories(geom_helpers
    SYSTEM BEFORE PUBLIC
        ${LIB2GEOM_INCLUDE_DIRS}
)
target_link_libraries(geom_helpers ${LIB2GEOM_LIBRARIES})
