project("MMDApp")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS" 
    LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
    )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/DirectXTex
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/Common
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC Engine)
