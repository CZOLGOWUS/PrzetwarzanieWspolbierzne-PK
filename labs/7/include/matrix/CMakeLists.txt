#----------first agument (it's a name of the lib) can be whatever
#
#----------there is no need to write "adder.hpp" 
#----------but it makes 2 files into a librarya and not just .cpp it works cuz it has definition and implementation
add_library(matrix Matrix.cpp Matrix.hpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(matrix PUBLIC OpenMP::OpenMP_CXX)
endif()