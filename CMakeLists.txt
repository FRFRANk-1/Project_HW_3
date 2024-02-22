cmake_minimum_required(VERSION 3.5.0)
project(Project_HW_3 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package( Opencv REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
add_executable(Project_HW_3 
main.cpp
TaskRunner.cpp
ImageProcessor.cpp
)

target_compile_features(Project_HW_3 PUBLIC cxx_std_17)
target_link_libraries(Project_HW_3 ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
