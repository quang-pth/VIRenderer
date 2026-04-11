project("EngineTests")

include(GoogleTest)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)

add_executable(${PROJECT_NAME} ${SRC_FILES})
add_test(NAME VIEngine_Functionality COMMAND ${PROJECT_NAME})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Vendor/DirectX-Headers/include
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/DirectXTex
    ${CMAKE_SOURCE_DIR}/Vendor/DirectXTex/Common
    ${CMAKE_SOURCE_DIR}/Vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/Vendor/googletest/googletest/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest Engine)

gtest_discover_tests(${PROJECT_NAME})
