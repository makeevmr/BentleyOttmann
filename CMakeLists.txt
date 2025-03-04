cmake_minimum_required(VERSION 3.20)

project(bentley_ottmann LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND TARGETS 
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

add_subdirectory(src)

add_executable(bentley_ottmann)
add_executable(generator)

target_link_libraries(bentley_ottmann PRIVATE ${TARGETS})

target_link_libraries(generator PRIVATE 
    gcd
    fraction
    point
    segment
    generate_data
)

# list(APPEND GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS
#     -Werror
#     -Wall
#     -Wextra
#     -Wpedantic
#     -Wcast-align
#     -Wcast-qual
#     -Wconversion
#     -Wctor-dtor-privacy
#     -Wenum-compare
#     -Wfloat-equal
#     -Wnon-virtual-dtor
#     -Wold-style-cast
#     -Woverloaded-virtual
#     -Wredundant-decls
#     -Wsign-conversion
#     -Wsign-promo
#     -g
# )
