add_library(morphing
    morphing.cpp
)

target_include_directories(morphing
    SYSTEM BEFORE PUBLIC
        ${LIB2GEOM_INCLUDE_DIRS}
)
target_link_libraries(morphing ${LIB2GEOM_LIBRARIES})
