cmake_minimum_required (VERSION 3.2)
project (AMR)
include_directories(${CMAKE_SOURCE_DIR}/source/hpp)

#set (AMR_DIM 3)
#set(AMR_MAX_LEVEL 2 CACHE STRING "Help message for this variable")
#set_property(
#  CACHE AMR_MAX_LEVEL
#  PROPERTY STRING
#  "2" "3" "4" "5" "6" "7" "8" "9" "10"
#)
#add_definitions( -DVERSION_LIBINTERFACE=${LIBINTERFACE_VERSION} )
#configure_file(Config.hpp.in ${CMAKE_SOURCE_DIR}/source/hpp/Config.hpp @ONLY)

add_executable(AMR
source/cpp/main.cpp
source/cpp/Geometry.cpp
source/cpp/MortonHasher.cpp
source/cpp/Vertex.cpp
source/cpp/Vector.cpp
source/cpp/Edge.cpp
source/cpp/Face.cpp
source/cpp/AABB.cpp
source/cpp/AABBTree.cpp
source/cpp/IntersectionTool.cpp
source/cpp/Mesh.cpp
)

install(TARGETS AMR DESTINATION ${CMAKE_SOURCE_DIR}/exe)
