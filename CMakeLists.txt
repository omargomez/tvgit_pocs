cmake_minimum_required(VERSION 4.0)

## Deps
# 1 libgit2

project(HelloWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(hello main.cpp)

find_package(libgit2 REQUIRED CONFIG)

# add_library(git2-cpp INTERFACE)
# target_include_directories(git2-cpp INTERFACE include/git2-cpp)


add_subdirectory(tvision) ## Submodule
## add_subdirectory(git2cpp)
# target_link_libraries(hello tvision libgit2::libgit2package git2-cpp)
target_link_libraries(hello tvision libgit2::libgit2package)



