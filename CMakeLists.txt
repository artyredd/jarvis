cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Jarvis)

file(GLOB jarvisHeaderFiles CONFIGURE_DEPENDS
     "Jarvis/Headers/jarvis/*.h"
)

file(GLOB jarvisSourceFiles CONFIGURE_DEPENDS
    "Jarvis/Source/*.c"
)

file(GLOB_RECURSE jarvisAssets CONFIGURE_DEPENDS
    "assets/*.*"
)

add_executable(Jarvis ${jarvisSourceFiles} ${jarvisHeaderFiles})

set_property(TARGET Jarvis PROPERTY COMPILE_WARNING_AS_ERROR ON)
set_target_properties(Jarvis PROPERTIES COMPILE_FLAGS "/std:c11 /ZI /Od /experimental:c11atomics")

include(FetchContent)

FetchContent_Populate(
    ferret
    GIT_REPOSITORY https://github.com/artyredd/SharpFerret.git
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/ferret
)

# Add the Ferret project as a subdirectory
add_subdirectory(external/Ferret)

# Ensure dependencies are built before the Jarvis target
add_dependencies(Jarvis Core Engine)

target_include_directories(Jarvis PRIVATE
    "external/Ferret/Core/Headers"
    "external/Ferret/Engine/Headers"
)

# Copy assets to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin/)

target_link_libraries(Jarvis PRIVATE
    Core
    Engine
)

set_target_properties(Jarvis PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
  LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
)

# copy plugins
# Ensure the directory exists before copying the file
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/bin/assets/plugins/TTSPlugin.dll
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/assets/plugins
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/../TTSPlugin/build/bin/TTSPlugin.dll ${CMAKE_BINARY_DIR}/bin/assets/plugins/TTSPlugin.dll
    DEPENDS ${CMAKE_SOURCE_DIR}/../TTSPlugin/build/bin/TTSPlugin.dll
    COMMENT "Copying TTSPlugin.dll to bin/assets/plugins directory..."
)

# Create a custom target that depends on the output of the custom command
add_custom_target(copy_files ALL
    DEPENDS ${CMAKE_BINARY_DIR}/bin/assets/plugins/TTSPlugin.dll
)

# Ensure your main target depends on the custom target
add_dependencies(Jarvis copy_files)