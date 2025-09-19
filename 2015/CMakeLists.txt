# create executable
add_executable(2015_1 main.1.cpp)

# day 2 details
add_executable(2015_2 main.2.cpp)
add_custom_command(
  TARGET 2015_2
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/2.txt
          ${CMAKE_BINARY_DIR}/2015/2.txt)
