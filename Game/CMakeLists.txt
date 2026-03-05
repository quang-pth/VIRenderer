project("Game")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC d3d12.lib d3dcompiler.lib dxgi.lib)

file(GLOB_RECURSE VERTEX_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/*.vs.hlsl CMAKE_CONFIGURE_DEPENDS)
set_source_files_properties(
    ${VERTEX_SHADERS} PROPERTIES
    VS_TOOL_OVERRIDE "HLSLCompiler"
    VS_SHADER_TYPE "Vertex"
    VS_SHADER_MODEL "5.0"
    VS_SHADER_ENTRYPOINT "main"
)

file(GLOB_RECURSE PIXEL_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shader/*.ps.hlsl CMAKE_CONFIGURE_DEPENDS)
set_source_files_properties(
    ${PIXEL_SHADERS} PROPERTIES
    VS_TOOL_OVERRIDE "HLSLCompiler"
    VS_SHADER_TYPE "Pixel"
    VS_SHADER_MODEL "5.0"
    VS_SHADER_ENTRYPOINT "main"
)

file(GLOB_RECURSE SHADER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shader/*.hlsl CMAKE_CONFIGURE_DEPENDS)
foreach(SHADER_FILE ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(SHADER_BINARY "${CMAKE_CURRENT_BINARY_DIR}/Shader/${SHADER_NAME}.cso")

    if(${SHADER_FILE} MATCHES ".*\\.vs\\.hlsl$")
        set(SHADER_PROFILE "vs_5_0")
    elseif(${SHADER_FILE} MATCHES ".*\\.ps\\.hlsl$")
        set(SHADER_PROFILE "ps_5_0")
    else()
        set(SHADER_PROFILE "lib_5_x")
    endif()

    add_custom_command(
        OUTPUT ${SHADER_BINARY}
        COMMAND dxc.exe /T ${SHADER_PROFILE} /E main /Fo ${SHADER_BINARY} ${SHADER_FILE}
        DEPENDS ${SHADER_FILE}
        COMMENT "Auto-compiling ${SHADER_PROFILE}: ${SHADER_FILE}"
    )
    
    list(APPEND SHADER_BINARIES ${SHADER_BINARY})
endforeach()

add_custom_target(CompileShaders ALL DEPENDS ${SHADER_BINARIES})
add_dependencies(${PROJECT_NAME} CompileShaders)

