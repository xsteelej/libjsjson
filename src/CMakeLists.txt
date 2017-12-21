project(jsjson)
file(GLOB_RECURSE SOURCES *.cpp)
add_library(jsjson ${SOURCES})
target_include_directories(jsjson PUBLIC ../src)
