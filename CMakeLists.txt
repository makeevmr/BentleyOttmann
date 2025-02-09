cmake_minimum_required(VERSION 3.20)

project(bentley_ottmann LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# use target_compile_options(<target_name> PUBLIC <flags_list>) for each translation unit or use approach below
set(GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-promo")

# set(GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo")


set(GCC_LINK_FLAGS "")

# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS} -g")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS} -O2 ")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_WARNINGS_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

add_subdirectory(src)

add_executable(bentley_ottmann)
add_executable(generator)

target_link_libraries(bentley_ottmann PRIVATE 
    gcd
    fraction
    point
    segment
    comparator
    read_data
    intersection
    begin_case
    end_case
    intersection_case
    main
)

target_link_libraries(generator PRIVATE 
    gcd
    fraction
    point
    segment
    generate_data
)
