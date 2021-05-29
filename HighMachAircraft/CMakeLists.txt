cmake_minimum_required(VERSiON 3.5)

project(HighMachAircraft VERSION 0.1 LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

aux_source_directory(. SRC_LIST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Headers)
add_executable(HighMachAircraft ${SRC_LIST})
