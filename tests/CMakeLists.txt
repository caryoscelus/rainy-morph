set(SINGLE_TEST_BINARY ON CACHE BOOL "Create single binary for all tests")

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
#             ${LIB2GEOM_INCLUDE_DIRS}
            ${CATCH_INCLUDE_DIRS}
    )
#     target_link_libraries(test_all ${LIB2GEOM_LIBRARIES})
    add_test(test_all test_all)
else()
    message(SEND_ERROR "Multiple test binaries support is not ready")
#     foreach (TEST_NAME ${ALL_TESTS})
#         add_executable(${TEST_NAME} main.cpp ${TEST_NAME})
#         
#     endforeach()
endif()
