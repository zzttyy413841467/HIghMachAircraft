cmake_minimum_required(VERSION 3.5)
SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(HighMachAircraft VERSION 0.1 LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
find_package(Armadillo CONFIG REQUIRED)
aux_source_directory(./HighMachAircraft/Sources SRC_LIST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HighMachAircraft/Headers)

add_executable(HighMachAircraft ${SRC_LIST})
target_link_libraries(HighMachAircraft PRIVATE ${ARMADILLO_LIBRARIES})
