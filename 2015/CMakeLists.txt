# day 1 details
add_executable(2015_1 main.1.cpp)
add_custom_command(
  TARGET 2015_1
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/1.txt
          ${CMAKE_BINARY_DIR}/2015/1.txt)

# day 2 details
add_executable(2015_2 main.2.cpp)
add_custom_command(
  TARGET 2015_2
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/2.txt
          ${CMAKE_BINARY_DIR}/2015/2.txt)

# day 3 details
add_executable(2015_3 main.3.cpp)
add_custom_command(
  TARGET 2015_3
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/3.txt
          ${CMAKE_BINARY_DIR}/2015/3.txt)

# day 4 details
add_executable(2015_4 main.4.cpp)
target_link_libraries(2015_4 ssl crypto)

# day 5 details
add_executable(2015_5 main.5.cpp)
add_custom_command(
  TARGET 2015_5
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/5.txt
          ${CMAKE_BINARY_DIR}/2015/5.txt)
