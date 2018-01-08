function(add_catch_test name)
    add_executable("test_${name}" main.cpp "${name}.cpp")
    add_test("test_${name}" "test_${name}")
    target_include_directories("test_${name}"
        SYSTEM BEFORE PUBLIC
            ${CATCH_INCLUDE_DIRS}
    )
endfunction()

add_catch_test(convert)
target_link_libraries(test_convert geom_helpers)

add_catch_test(morph)
target_link_libraries(test_morph morphing)

add_catch_test(bones)
target_link_libraries(test_bones geom_helpers)
