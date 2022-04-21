cmake_minimum_required(VERSION 3.16.3)

project(lab6)

add_executable(${PROJECT_NAME} src/main.cpp)


find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX matrix)
endif()

#----------------------------------------------------------builds library----------------------------------------------------------
#
add_subdirectory(include/matrix)

#----------------------------------------------------------tell compiler which libraries to include you want-----------------------
#----------------------------------------------------------makes it soo we can use <library.h> instead of "project_name/lib_folder"
#
target_include_directories(${PROJECT_NAME} PRIVATE include/matrix)

#---------------------------------------------------------tell compiler where libraries you want to link/include are--------------
#
target_link_directories(${PROJECT_NAME} PRIVATE include/matrix)

#---------------------------------------------------------links libaries to executable-----------------------------------------------
#
#target_compile_options(${PROJECT_NAME} PRIVATE -fopenmp)
