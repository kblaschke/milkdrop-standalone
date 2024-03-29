cmake_minimum_required(VERSION 3.5)
project(vis_milk2)

enable_language(ASM_NASM)

find_package(projectM-Eval REQUIRED COMPONENTS Milkdrop)

remove_definitions(-DNOMINMAX)

set( SHADER_FILES dx11/DefaultVertexShader.hlsl
                  dx11/DiffusePixelShader.hlsl
                  dx11/ColorPixelShader.hlsl
                  dx11/TexturePixelShader.hlsl
                  dx11/Texture2PixelShader.hlsl )
set( SHADER_INCLUDES )

foreach( SHADER_FILE ${SHADER_FILES} )
  get_filename_component( FileName ${SHADER_FILE} NAME_WE )
  if(${FileName} MATCHES "(.+Vertex.+)")
    set(ShaderType vs)
  elseif(${FileName} MATCHES "(.+Pixel.+)")
    set(ShaderType ps)
  else()
    message(FATAL_ERROR "Unknown shader type.")
  endif()
  set( IncFile ${FileName}.inc )
  list( APPEND SHADER_INCLUDES ${IncFile} )

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${IncFile}
    COMMAND fxc /nologo /T${ShaderType}_4_0_level_9_1 /Vn ${FileName}Code /Fh ${IncFile} ${SHADER_FILE}
    MAIN_DEPENDENCY ${SHADER_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endforeach(SHADER_FILE)

set(SOURCES dx11/CommonStates.cpp
            dx11/ConstantTable.cpp
            dx11/DDSTextureLoader.cpp
            dx11/WICTextureLoader.cpp
            dx11/DX11Context.cpp
            vis_milk2/dxcontext.cpp
            vis_milk2/fft.cpp
            vis_milk2/milkdropfs.cpp
            vis_milk2/plugin.cpp
            vis_milk2/pluginshell.cpp
            vis_milk2/state.cpp
            vis_milk2/support.cpp
            vis_milk2/texmgr.cpp
            vis_milk2/utility.cpp)

set(SOURCES_NSEEL
    ns-eel2/nseel-caltab.c
    ns-eel2/nseel-cfunc.c
    ns-eel2/nseel-compiler.c
    ns-eel2/nseel-eval.c
    ns-eel2/nseel-lextab.c
    ns-eel2/nseel-ram.c
    ns-eel2/nseel-yylex.c
    )
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SOURCES_NSEEL ${SOURCES_NSEEL}
        ns-eel2/asm-nseel-x64.asm
        )
endif()

if(CORE_SYSTEM_NAME STREQUAL windowsstore)
  add_definitions(-D_WIN32_WINNT=0x0A00 -D_WINDOWS -D_CRT_NON_CONFORMING_SWPRINTFS)
else()
  add_definitions(-D_WIN32_WINNT=0x0600 -D_WINDOWS)
endif()
add_library(vis_milk2 STATIC ${SOURCES} ${SHADER_INCLUDES})
add_library(vis_milk2_nseel2 STATIC ${SOURCES} ${SOURCES_NSEEL} ${SHADER_INCLUDES})

target_include_directories(vis_milk2_nseel2
    PUBLIC
    ${CMAKE_SOURCE_DIR}/ns-eel2
    )

target_link_libraries(vis_milk2
    PUBLIC
    projectM::Eval
    projectM::ns-eel2
    )

add_executable(Milkdrop2StandAlone WIN32 StandAlone.cpp)
set_target_properties(Milkdrop2StandAlone PROPERTIES
    VS_DPI_AWARE ON
)
target_link_libraries(Milkdrop2StandAlone
    vis_milk2
    d3d11
    )
add_executable(Milkdrop2NSEEL2 WIN32 StandAlone.cpp)
set_target_properties(Milkdrop2NSEEL2 PROPERTIES
    VS_DPI_AWARE ON
    )
target_link_libraries(Milkdrop2NSEEL2
    vis_milk2_nseel2
    d3d11
    )



add_executable(EvalTestNSEEL2
    ${SOURCES_NSEEL}
    EvalTest.cpp
    )
target_include_directories(EvalTestNSEEL2
    PUBLIC
    ${CMAKE_SOURCE_DIR}/ns-eel2
    )

add_executable(EvalTestProjectMEval
    EvalTest.cpp
    )
target_link_libraries(EvalTestProjectMEval
    PUBLIC
    projectM::Eval
    projectM::ns-eel2
    )
