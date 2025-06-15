cmake_minimum_required(VERSION 3.22.0)

project(cmake-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ASAN "Enable asan memory tools" OFF)

if(ENABLE_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

# ccache
find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
  message(STATUS "### use ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else()
  message(WARNING "Not found ccache, install it with 'sudo apt install ccache'")
endif()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_SYSROOT: ${CMAKE_SYSROOT}")
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
target_include_directories(main
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)
install(TARGETS main
  DESTINATION bin
)