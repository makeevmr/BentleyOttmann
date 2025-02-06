cmake_minimum_required(VERSION 3.20)

project(BentleyOttmann LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# use target_compile_options(<target_name> PUBLIC <flags_list>) for each translation unit or use approach below
set(GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo")

set(GCC_LINK_FLAGS "")

# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

add_subdirectory(src)
# add_subdirectory(tests)

# enable_testing()

# find_package(GTest REQUIRED)


add_executable(bentley_ottmann)

target_link_libraries(bentley_ottmann PRIVATE 
    comparator
    find_intersection
    fraction
    gcd
    point
    segment
    bentley_ottmann_lib
    # GTest::GTest
    # graph_validation
    # automated_adj_list_testing
)
# add_test(lab3_adj_list_gtests lab3_adj_list_tests)

# add_executable(lab3_adj_matrix_tests)
# target_link_libraries(lab3_adj_matrix_tests PRIVATE 
#     GTest::GTest
#     graph_validation
#     automated_adj_matrix_testing
# )
# add_test(lab3_adj_matrix_gtests lab3_adj_matrix_tests)
