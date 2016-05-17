project(visualization.milkdrop2)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/lib/vis_milk2
                    ${KODI_INCLUDE_DIR})

set(MD2_SOURCES src/Milkdrop2XBMC.cpp)

add_subdirectory(lib/vis_milk2)

set(DEPLIBS vis_milk2)

build_addon(visualization.milkdrop2 MD2 DEPLIBS)

add_executable(Milkdrop2StandAlone EXCLUDE_FROM_ALL src/StandAlone.cpp)
target_link_libraries(Milkdrop2StandAlone ${DEPLIBS})

include(CPack)
