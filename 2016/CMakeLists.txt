set(SHARED_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared")


foreach(DAY RANGE 1 1)
  set(TARGET_NAME "2016_${DAY}")

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
              ${CMAKE_BINARY_DIR}/2016/${DAY}.txt)
  endif()
endforeach()
