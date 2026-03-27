project("Engine")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp CMAKE_CONFIGURE_DEPENDS)

if(WIN32)
    file(GLOB_RECURSE WINDOW_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Windows/*.cpp CMAKE_CONFIGURE_DEPENDS)
    list(APPEND SRC_FILES ${WINDOW_SRC_FILES})
endif()

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS" 
    LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
    )
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core/pch.h)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/DirectXTex
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/Common
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC d3d12 d3dcompiler dxgi DirectXTex spdlog)

file(GLOB_RECURSE VERTEX_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/*.vs.hlsl CMAKE_CONFIGURE_DEPENDS)
set(VS_HLSL_ENTRY_POINT "BasicVS")
set_source_files_properties(
    ${VERTEX_SHADERS} PROPERTIES
    VS_TOOL_OVERRIDE "HLSLCompiler"
    VS_SHADER_TYPE "Vertex"
    VS_SHADER_MODEL "5.0"
    VS_SHADER_ENTRYPOINT ${VS_HLSL_ENTRY_POINT}
)

set(PS_HLSL_ENTRY_POINT "BasicPS")
file(GLOB_RECURSE PIXEL_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shader/*.ps.hlsl CMAKE_CONFIGURE_DEPENDS)
set_source_files_properties(
    ${PIXEL_SHADERS} PROPERTIES
    VS_TOOL_OVERRIDE "HLSLCompiler"
    VS_SHADER_TYPE "Pixel"
    VS_SHADER_MODEL "5.0"
    VS_SHADER_ENTRYPOINT ${PS_HLSL_ENTRY_POINT}
)

file(GLOB_RECURSE SHADER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shader/*.hlsl CMAKE_CONFIGURE_DEPENDS)
foreach(SHADER_FILE ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(SHADER_BINARY "${CMAKE_CURRENT_BINARY_DIR}/Shader/${SHADER_NAME}.cso")

    if(${SHADER_FILE} MATCHES ".*\\.vs\\.hlsl$")
        set(SHADER_PROFILE "vs_5_0")
        set(ENTRY_POINT ${VS_HLSL_ENTRY_POINT})
    elseif(${SHADER_FILE} MATCHES ".*\\.ps\\.hlsl$")
        set(SHADER_PROFILE "ps_5_0")
        set(ENTRY_POINT ${PS_HLSL_ENTRY_POINT})
    else()
        set(SHADER_PROFILE "lib_5_x")
    endif()

    add_custom_command(
        OUTPUT ${SHADER_BINARY}
        COMMAND dxc.exe /T ${SHADER_PROFILE} /E ${ENTRY_POINT} /Fo ${SHADER_BINARY} ${SHADER_FILE}
        DEPENDS ${SHADER_FILE}
        COMMENT "Auto-compiling ${SHADER_PROFILE}: ${SHADER_FILE}"
    )
    
    list(APPEND SHADER_BINARIES ${SHADER_BINARY})
endforeach()

add_custom_target(EngineCompileHLSLShaders ALL DEPENDS ${SHADER_BINARIES})
add_dependencies(${PROJECT_NAME} EngineCompileHLSLShaders)

