cmake_minimum_required(VERSION 3.12)
project(_pyboost VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Add "cmake" folder
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Enable ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

# Boost and Python
set(PY_VERSION 3)

find_package(Boost REQUIRED COMPONENTS system python${PY_VERSION})
find_package(PythonLibs ${PY_VERSION} REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} include)  # TODO: Don't include 'include'

# Add pyboost library target
set(SOURCE_FILES src/pyboost.cpp)
set(HEADER_FILES )

python_add_module(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(src)
