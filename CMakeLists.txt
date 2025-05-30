cmake_minimum_required(VERSION 3.24)
project(MicroViewerBackend)

set(CMAKE_CXX_STANDARD 23)

file (GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES INCLUDE_DIRS)

add_executable(${PROJECT_NAME} ${SOURCES})

# REST library
include(FetchContent)
FetchContent_Declare(Pistache
        GIT_REPOSITORY https://github.com/pistacheio/pistache.git
        GIT_TAG v0.4.25
        SOURCE_DIR "Pistache")
FetchContent_MakeAvailable(Pistache)

add_custom_target(PistacheBuild)
add_custom_command(
        TARGET PistacheBuild
        PRE_BUILD
        COMMAND echo PRE_BUILD: Building Pistache...
        COMMAND meson setup build
        COMMAND meson compile -C build
        COMMAND echo PRE_BUILD: Pistache build success!
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Pistache)

add_dependencies(${PROJECT_NAME} PistacheBuild)

# RapidJSON for returning data
include(FetchContent)
FetchContent_Declare(RapidJSON
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        SOURCE_DIR "RapidJSON")
FetchContent_MakeAvailable(RapidJSON)

# Postgresql binding
#find_package(libpqxx REQUIRED)
include(FetchContent)
FetchContent_Declare(libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        SOURCE_DIR "libpqxx")
FetchContent_MakeAvailable(libpqxx)

add_custom_target(IncrementBuildNumber)
add_custom_command(
        TARGET IncrementBuildNumber
        PRE_BUILD
        COMMAND chmod +x ${PROJECT_SOURCE_DIR}/increment.sh
        COMMAND bash ${PROJECT_SOURCE_DIR}/increment.sh
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_dependencies(${PROJECT_NAME} IncrementBuildNumber)

include_directories(${INCLUDE_DIRS} "${PROJECT_BINARY_DIR}/Pistache/include/" "${PROJECT_BINARY_DIR}/RapidJSON/include/" "${PROJECT_BINARY_DIR}/libpqxx/include/")

# check added so that cmake is happy when the dir doesn't exist yet
if (EXISTS "${PROJECT_BINARY_DIR}/Pistache/build/src/libpistache.so")
    target_link_libraries(${PROJECT_NAME} "${PROJECT_BINARY_DIR}/Pistache/build/src/libpistache.so" pqxx)
else()
    message("First compilation, creating a libpistache.so dummy, it will be recreated before linking")
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Pistache/build")
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Pistache/build/src")
    file(TOUCH "${PROJECT_BINARY_DIR}/Pistache/build/src/libpistache.so")
    target_link_libraries(${PROJECT_NAME} "${PROJECT_BINARY_DIR}/Pistache/build/src/libpistache.so" pqxx)
endif()