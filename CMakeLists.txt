project(Kmeans_Kneighbour)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_library(CsvRW STATIC csvrw.cpp csvrw.h pointvector.h kmeans.cpp
kmeans.h knearest.cpp knearest.h draw_clusters.cpp draw_clusters.h)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} CsvRW ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mall_data.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
