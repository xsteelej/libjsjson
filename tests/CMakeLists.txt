add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(test_libjsjson ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries (test_libjsjson LINK_PUBLIC jsjson Catch)

set(testCommand ${PROJECT_SOURCE_DIR}/bin/test_libjsjson)

#JSON String parsing tests
add_test(NAME top_level_object_empty_dictionary COMMAND ${testCommand} [top_level_object_empty_dictionary])
add_test(NAME top_level_object_empty_array COMMAND ${testCommand} [top_level_object_empty_array])
add_test(NAME top_level_object_boolean COMMAND ${testCommand} [top_level_object_boolean])
add_test(NAME top_level_object_string COMMAND ${testCommand} [top_level_object_string])
add_test(NAME top_level_object_number COMMAND ${testCommand} [top_level_object_number])
add_test(NAME top_level_object_dictionray COMMAND ${testCommand} [top_level_object_dictionary])
add_test(NAME top_level_object_array COMMAND ${testCommand} [top_level_object_array])
add_test(NAME top_level_object_dictionary+array COMMAND ${testCommand} [top_level_object_dictionary+array])

#JSON Object creation tests
add_test(NAME json_object_creation_dictionary COMMAND ${testCommand} [json_object_creation_dictionary])
add_test(NAME json_object_creation_array COMMAND ${testCommand} [json_object_creation_array])

#JSON error handling tests
add_test(NAME error_handling_garbage COMMAND ${testCommand} [error_handling_garbage])
add_test(NAME error_handling_invalid_after_comma COMMAND ${testCommand} [error_handling_invalid_after_comma])
add_test(NAME error_handling_no_colon_after_key COMMAND ${testCommand} [error_handling_no_colon_after_key] )
add_test(NAME error_handling_no_quote_before_dictionary_key COMMAND ${testCommand} [error_handling_no_quote_before_dictionary_key])
add_test(NAME error_handling_no_quote_after_dictionary_key COMMAND ${testCommand} [error_handling_no_quote_after_dictionary_key])
add_test(NAME error_handling_invalid_chars_after_element COMMAND ${testCommand} [error_handling_invalid_chars_after_element] )
add_test(NAME error_handling_invalid_boolean COMMAND ${testCommand} [error_handling_invalid_boolean] )
