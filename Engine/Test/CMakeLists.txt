project("EngineTests")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/TestApplication.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp CMAKE_CONFIGURE_DEPENDS)

if(WIN32)
    file(GLOB_RECURSE DX12_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Renderer/DX12/*.cpp CMAKE_CONFIGURE_DEPENDS)
    list(APPEND SRC_FILES ${DX12_SRC_FILES})
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/DirectXTex
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/Common
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Vendor/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/Vendor/glm
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest Engine glm)

include(GoogleTest)
enable_testing()
gtest_discover_tests(${PROJECT_NAME})
gtest_add_tests(TARGET ${PROJECT_NAME})
