project(vis_milk2)

enable_language(C)
enable_language(CXX)

cmake_minimum_required(VERSION 2.6)

remove_definitions(-DNOMINMAX)

set(SOURCES ns-eel2/nseel-caltab.c
            ns-eel2/nseel-cfunc.c
            ns-eel2/nseel-compiler.c
            ns-eel2/nseel-eval.c
            ns-eel2/nseel-lextab.c
            ns-eel2/nseel-ram.c
            ns-eel2/nseel-yylex.c
            vis_milk2/dxcontext.cpp
            vis_milk2/fft.cpp
            vis_milk2/milkdropfs.cpp
            vis_milk2/plugin.cpp
            vis_milk2/pluginshell.cpp
            vis_milk2/state.cpp
            vis_milk2/support.cpp
            vis_milk2/texmgr.cpp
            vis_milk2/utility.cpp)

add_library(vis_milk2 STATIC ${SOURCES})
