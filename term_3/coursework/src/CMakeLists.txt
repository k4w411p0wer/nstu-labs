add_subdirectory(tests)


set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -NDEBUG")

add_executable(
  bin main.cpp
  sorted_string_array.hpp sorted_string_array.cpp
  commands.hpp commands.cpp
)
