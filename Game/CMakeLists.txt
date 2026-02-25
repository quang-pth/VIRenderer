project("Game")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC d3d12.lib d3dcompiler.lib dxgi.lib)