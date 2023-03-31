cmake_minimum_required(VERSION 3.0.0)
# vcpkg integration - override cmake toolchain (note: should be placed before project() call)
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(vcpkgdemo VERSION 0.1.0)

# Lets use modern standard
set(CMAKE_CXX_STANDARD 17)

add_executable(vcpkg_demo src/auction.cpp)

