add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE .)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(test_libjsjson ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries (test_libjsjson LINK_PUBLIC libjsjson Catch)

set(testCommand ${PROJECT_SOURCE_DIR}/bin/test_libjsjson)

#JSON String parsing tests
add_test(NAME top_level_object_empty_dictionary COMMAND ${testCommand})
add_test(NAME top_level_object_empty_array COMMAND ${testCommand})
add_test(NAME top_level_object_boolean COMMAND ${testCommand})
add_test(NAME top_level_object_string COMMAND ${testCommand})
add_test(NAME top_level_object_number COMMAND ${testCommand})
add_test(NAME top_level_object_dictionray COMMAND ${testCommand})
add_test(NAME top_level_object_array COMMAND ${testCommand})
add_test(NAME top_level_object_dictionary+array COMMAND ${testCommand})

#JSON Object creation tests
add_test(NAME json_object_creation_dictionary COMMAND ${testCommand})
