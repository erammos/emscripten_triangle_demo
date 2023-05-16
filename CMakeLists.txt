cmake_minimum_required(VERSION 3.15)
project(fluffy)
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Use cmake -Bbuild . \n")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create an option to switch between a system sdl library and a vendored sdl library
option(MYGAME_VENDORED "Use vendored libraries" OFF)

if(MYGAME_VENDORED)
    add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()
add_executable(${PROJECT_NAME} src/main.cc)
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
if (EMSCRIPTEN)
        set(CMAKE_EXECUTABLE_SUFFIX ".html")
        file(COPY templates DESTINATION ${CMAKE_BINARY_DIR})
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--shell-file templates/shell_minimal.html")
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
