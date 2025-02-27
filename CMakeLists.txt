cmake_minimum_required(VERSION 3.10)
project(CryptoPriceTracker)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the path to vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Users/kashm/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find the required packages
find_package(cpr CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(ZLIB REQUIRED)  # Ensure Zlib is found

# Add the executable
add_executable(CryptoPriceTracker C:/Users/kashm/Desktop/CryptoPriceTracker/CryptoPriceTracker/CryptoPriceTracker.cpp)

# Link the libraries
target_link_libraries(CryptoPriceTracker PRIVATE cpr::cpr jsoncpp_lib ZLIB::ZLIB)
