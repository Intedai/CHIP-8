cmake_minimum_required(VERSION 3.28)
project(CHIP-8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB SOURCES "src/*.cpp")

include(FetchContent)
# TOML 11
FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
  GIT_TAG        v4.4.0
)
FetchContent_MakeAvailable(toml11)

# SFML 2.6.2
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(CHIP-8 ${SOURCES})

# Includes
target_include_directories(CHIP-8 PRIVATE include)
target_link_libraries(CHIP-8 PRIVATE
    toml11::toml11
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)
target_compile_features(CHIP-8 PRIVATE cxx_std_17)

# Copy the config file to the same dir as the compiled binary (/bin)
add_custom_command(
    TARGET CHIP-8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/config.toml
    $<TARGET_FILE_DIR:CHIP-8>
)

# Copy the tests to the same dir as the compiled binary (/bin)
add_custom_command(
    TARGET CHIP-8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/tests
    $<TARGET_FILE_DIR:CHIP-8>/tests
)

if(WIN32)
    add_custom_command(
        TARGET CHIP-8
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CHIP-8>
        VERBATIM)
endif()