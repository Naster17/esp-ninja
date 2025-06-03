# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.c)

set(app_include ${CMAKE_SOURCE_DIR}/src/kernel/include
  # ${CMAKE_SOURCE_DIR}/src/another_include
)

idf_component_register(SRCS ${app_sources} INCLUDE_DIRS ${app_include})
