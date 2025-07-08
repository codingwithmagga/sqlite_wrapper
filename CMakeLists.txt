cmake_minimum_required(VERSION 3.25)

project(sqlite_wrapper LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Preparing third-party library 'sqlite3'")

include(FetchContent)
FetchContent_Declare(
    sqlite3
    URL https://www.sqlite.org/2025/sqlite-amalgamation-3500200.zip
    # CMake policy 'CMP0135'
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Use 'Populate' command to prevent creating duplicated target libraries
if(NOT sqlite3_POPULATED)
    FetchContent_MakeAvailable(sqlite3)

    # Create target to make 'sqlite3' available as library
    add_library(sqlite3 "${sqlite3_SOURCE_DIR}/sqlite3.c")
       
    # Make include file available through 'sqlite3' target
    target_include_directories(sqlite3 PUBLIC "${sqlite3_SOURCE_DIR}")
endif()

add_library(sqlite_wrapper
    src/database.cpp
    src/sqlite3_wrapper.cpp
)

target_include_directories(sqlite_wrapper
    PUBLIC
        include
)

target_link_libraries(sqlite_wrapper
    PRIVATE
        sqlite3
)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(database_tests
    tests/database_tests.cpp
)

target_link_libraries(database_tests
    PRIVATE
        gtest_main
        gmock_main
        sqlite_wrapper
)

include(GoogleTest)
gtest_discover_tests(database_tests)