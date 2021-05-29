cmake_minimum_required(VERSION 3.5)

project(HighMachAircraft VERSION 0.1 LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

aux_source_directory(./HighMachAircraft/Sources SRC_LIST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HighMachAircraft/Headers)
add_executable(HighMachAircraft ${SRC_LIST})
