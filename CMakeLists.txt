# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(hikvision_api VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set installation paths
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/hikvision_api)
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)

# Source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
    ${PROJECT_SOURCE_DIR}/src/timer.cpp
)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/utils.h
    ${PROJECT_SOURCE_DIR}/include/timer.h
)

# Build the main executable
add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp ${SOURCES})
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link libraries required for the main executable
target_link_libraries(main PRIVATE
    pthread
    MvCameraControl # Assuming this is the name of the external library
)
target_link_directories(main PRIVATE $ENV{MVCAM_COMMON_RUNENV}/64)
target_compile_options(main PRIVATE -g) # Enable debugging symbols
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Build the static library
add_library(hikvision_api STATIC ${SOURCES})
set_target_properties(hikvision_api PROPERTIES OUTPUT_NAME hikvision_api)
target_include_directories(hikvision_api PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Installation rules
install(TARGETS hikvision_api
    ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
)

install(FILES ${HEADERS}
    DESTINATION ${INSTALL_INCLUDE_DIR}
)

# Custom "clean" target - not strictly necessary, since CMake already provides a clean option
add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/build
    COMMENT "Cleaning build directory"
)

# Add custom "run" target
add_custom_target(run
    COMMAND ${PROJECT_SOURCE_DIR}/build/main
    DEPENDS main
    COMMENT "Running the main executable"
)