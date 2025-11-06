cmake_minimum_required(VERSION 3.8)

project(SceneGL VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_BUILD_TYPE            Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# git submodule
find_package(Git REQUIRED)
if (NOT EXISTS ${LIBTFD_DIR}/CMakeLists.txt)
    execute_process(COMMAND ${GIT_EXECUTABLE}
        submodule update --init --recursive
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()

# create static library
set(INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set(PRIVATE_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
file(GLOB_RECURSE SRC_FILES "src/**.cpp")
message(STATUS "INCLUDE_DIRS: " ${INCLUDE_DIRS})
message(STATUS "PRIVATE_INCLUDE_DIRS: " ${PRIVATE_INCLUDE_DIRS})
message(STATUS "SRC_FILES: ${SRC_FILES}")

add_executable(cpp_101 ${SRC_FILES})
target_include_directories(cpp_101 PUBLIC ${INCLUDE_DIRS})
target_include_directories(cpp_101 PRIVATE ${PRIVATE_INCLUDE_DIRS})
