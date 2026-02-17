set(SHARED_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared")

include(FetchContent)

# Fetch nlohmann/json for day 12
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

foreach(DAY RANGE 1 22)
  set(TARGET_NAME "2015_${DAY}")

  add_executable(${TARGET_NAME} main.${DAY}.cpp)
  target_compile_options(${TARGET_NAME} PUBLIC -coverage)
  target_link_options(${TARGET_NAME} PUBLIC -coverage)
  target_include_directories(${TARGET_NAME} PRIVATE ${SHARED_INCLUDE_DIR})

  # Copy input file if it exists
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${DAY}.txt")
    add_custom_command(
      TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${CMAKE_CURRENT_SOURCE_DIR}/${DAY}.txt
              ${CMAKE_BINARY_DIR}/2015/${DAY}.txt)
  endif()
endforeach()

# Day-specific dependencies
target_link_libraries(2015_4 ssl crypto)
target_link_libraries(2015_12 PRIVATE nlohmann_json::nlohmann_json)
