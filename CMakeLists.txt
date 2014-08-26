project(visualization.milkdrop2)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(xbmc REQUIRED)
find_package(DirectX REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/lib/vis_milk2
                    ${DirectX_INCLUDE_DIR}
                    ${XBMC_INCLUDE_DIR})

set(MD2_SOURCES src/Milkdrop2XBMC.cpp)

add_subdirectory(lib/vis_milk2)

set(DEPLIBS vis_milk2 ${DirectX_LIBRARY})

build_addon(visualization.milkdrop2 MD2 DEPLIBS)

add_executable(StandAlone src/StandAlone.cpp EXCLUDE_FROM_ALL)
target_link_libraries(StandAlone ${DEPLIBS})

include(CPack)
