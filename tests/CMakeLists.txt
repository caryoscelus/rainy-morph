set(SINGLE_TEST_BINARY OFF CACHE BOOL "Create single binary for all tests")

set(ALL_TESTS
    morph
    convert
)

if (${SINGLE_TEST_BINARY})
    add_executable(test_all main.cpp ${ALL_TESTS})
    target_link_libraries(test_all fmt)
    target_link_libraries(test_all geom_helpers)
    target_link_libraries(test_all morphing)
    target_include_directories(test_all
        SYSTEM BEFORE PUBLIC
            ${CATCH_INCLUDE_DIRS}
    )
    add_test(test_all test_all)
else()
    foreach (TEST_NAME ${ALL_TESTS})
        add_executable(${TEST_NAME} main.cpp ${TEST_NAME}.cpp)
        target_link_libraries(${TEST_NAME} fmt)
        target_link_libraries(${TEST_NAME} geom_helpers)
        target_link_libraries(${TEST_NAME} morphing)
        target_include_directories(${TEST_NAME}
            SYSTEM BEFORE PUBLIC
                ${CATCH_INCLUDE_DIRS}
        )
        add_test(${TEST_NAME} ${TEST_NAME})
    endforeach()
endif()
