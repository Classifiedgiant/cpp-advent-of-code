set(SHARED_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared")

include(FetchContent)

# day 1 details
add_executable(2015_1 main.1.cpp)
target_compile_options(2015_1 PUBLIC -coverage)
target_link_options(2015_1 PUBLIC -coverage)
add_custom_command(
  TARGET 2015_1
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/1.txt
          ${CMAKE_BINARY_DIR}/2015/1.txt)

# day 2 details
add_executable(2015_2 main.2.cpp)
target_compile_options(2015_2 PUBLIC -coverage)
target_link_options(2015_2 PUBLIC -coverage)
add_custom_command(
  TARGET 2015_2
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/2.txt
          ${CMAKE_BINARY_DIR}/2015/2.txt)

# day 3 details
add_executable(2015_3 main.3.cpp)
target_compile_options(2015_3 PUBLIC -coverage)
target_link_options(2015_3 PUBLIC -coverage)
add_custom_command(
  TARGET 2015_3
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/3.txt
          ${CMAKE_BINARY_DIR}/2015/3.txt)

# day 4 details
add_executable(2015_4 main.4.cpp)
target_compile_options(2015_4 PUBLIC -coverage)
target_link_options(2015_4 PUBLIC -coverage)
target_link_libraries(2015_4 ssl crypto)

# day 5 details
add_executable(2015_5 main.5.cpp)
target_compile_options(2015_5 PUBLIC -coverage)
target_link_options(2015_5 PUBLIC -coverage)
add_custom_command(
        TARGET 2015_5
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/5.txt
        ${CMAKE_BINARY_DIR}/2015/5.txt)

# day 6 details
add_executable(2015_6 main.6.cpp)
target_compile_options(2015_6 PUBLIC -coverage)
target_link_options(2015_6 PUBLIC -coverage)
add_custom_command(
  TARGET 2015_6
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/6.txt
          ${CMAKE_BINARY_DIR}/2015/6.txt)

# day 7 details
add_executable(2015_7 main.7.cpp)
target_compile_options(2015_7 PUBLIC -coverage)
target_link_options(2015_7 PUBLIC -coverage)
add_custom_command(
        TARGET 2015_7
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/7.txt
        ${CMAKE_BINARY_DIR}/2015/7.txt)

# day 8 details
add_executable(2015_8 main.8.cpp)
target_compile_options(2015_8 PUBLIC -coverage)
target_link_options(2015_8 PUBLIC -coverage)
add_custom_command(
        TARGET 2015_8
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/8.txt
        ${CMAKE_BINARY_DIR}/2015/8.txt)

# day 9 details
add_executable(2015_9 main.9.cpp)
target_compile_options(2015_9 PUBLIC -coverage)
target_link_options(2015_9 PUBLIC -coverage)
target_include_directories(2015_9 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_9
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/9.txt
        ${CMAKE_BINARY_DIR}/2015/9.txt)

# day 10 details
add_executable(2015_10 main.10.cpp)
target_compile_options(2015_10 PUBLIC -coverage)
target_link_options(2015_10 PUBLIC -coverage)

# day 11 details
add_executable(2015_11 main.11.cpp)
target_compile_options(2015_11 PUBLIC -coverage)
target_link_options(2015_11 PUBLIC -coverage)

# day 12 details
add_executable(2015_12 main.12.cpp)
target_compile_options(2015_12 PUBLIC -coverage)
target_link_options(2015_12 PUBLIC -coverage)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)
target_link_libraries(2015_12 PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(2015_12 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_12
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/12.txt
        ${CMAKE_BINARY_DIR}/2015/12.txt)

# day 13 details
add_executable(2015_13 main.13.cpp)
target_compile_options(2015_13 PUBLIC -coverage)
target_link_options(2015_13 PUBLIC -coverage)
target_include_directories(2015_13 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_13
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/13.txt
        ${CMAKE_BINARY_DIR}/2015/13.txt)

# day 14 details
add_executable(2015_14 main.14.cpp)
target_compile_options(2015_14 PUBLIC -coverage)
target_link_options(2015_14 PUBLIC -coverage)
target_include_directories(2015_14 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_14
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/14.txt
        ${CMAKE_BINARY_DIR}/2015/14.txt)

# day 15 details
add_executable(2015_15 main.15.cpp)
target_compile_options(2015_15 PUBLIC -coverage)
target_link_options(2015_15 PUBLIC -coverage)
target_include_directories(2015_15 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_15
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/15.txt
        ${CMAKE_BINARY_DIR}/2015/15.txt)

# day 16 details
add_executable(2015_16 main.16.cpp)
target_compile_options(2015_16 PUBLIC -coverage)
target_link_options(2015_16 PUBLIC -coverage)
target_include_directories(2015_16 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_16
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/16.txt
        ${CMAKE_BINARY_DIR}/2015/16.txt)

# day 17 details
add_executable(2015_17 main.17.cpp)
target_compile_options(2015_17 PUBLIC -coverage)
target_link_options(2015_17 PUBLIC -coverage)
target_include_directories(2015_17 PRIVATE ${SHARED_INCLUDE_DIR})

# day 18 details
add_executable(2015_18 main.18.cpp)
target_compile_options(2015_18 PUBLIC -coverage)
target_link_options(2015_18 PUBLIC -coverage)
target_include_directories(2015_18 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_18
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/18.txt
        ${CMAKE_BINARY_DIR}/2015/18.txt)

# day 19 details
add_executable(2015_19 main.19.cpp)
target_compile_options(2015_19 PUBLIC -coverage)
target_link_options(2015_19 PUBLIC -coverage)
target_include_directories(2015_19 PRIVATE ${SHARED_INCLUDE_DIR})
add_custom_command(
        TARGET 2015_19
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/2015/19.txt
        ${CMAKE_BINARY_DIR}/2015/19.txt)
