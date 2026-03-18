cmake_minimum_required (VERSION 3.11)

project ("VIRenderer" VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(Game)
add_subdirectory(Vendor/DirectX-Headers)
add_subdirectory(Vendor/DirectXTex)
# add_subdirectory(Vendors/lua)
# add_subdirectory(Vendors/box2d)