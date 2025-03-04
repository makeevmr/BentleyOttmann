cmake_minimum_required(VERSION 3.20)

project(bentley_ottmann LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS "\
-Werror \
-Wall \
-Wextra \
-Wpedantic \
-Wcast-align \
-Wcast-qual \
-Wconversion \
-Wctor-dtor-privacy \
-Wenum-compare \
-Wfloat-equal \
-Wnon-virtual-dtor \
-Wold-style-cast \
-Woverloaded-virtual \
-Wredundant-decls \
-Wsign-promo \
-g \
")

# set(GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS "\
# -Werror \
# -Wall \
# -Wextra \
# -Wpedantic \
# -Wcast-align \
# -Wcast-qual \
# -Wconversion \
# -Wctor-dtor-privacy \
# -Wenum-compare \
# -Wfloat-equal \
# -Wnon-virtual-dtor \
# -Wold-style-cast \
# -Woverloaded-virtual \
# -Wredundant-decls \
# -Wsign-conversion \
# -Wsign-promo \
# -g \
# ")


set(GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS "\
-DNDEBUG \
-O2 \
")

add_subdirectory(src)

add_executable(bentley_ottmann)
add_executable(generator)

if(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "RELEASE BUILD TYPE")
    target_compile_options(bentley_ottmann   PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(gcd               PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(fraction          PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(point             PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(segment           PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(comparator        PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(read_data         PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(intersection      PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(begin_case        PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(end_case          PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(intersection_case PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(main              PUBLIC SHELL:${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "DEBUG BUILD TYPE")
    target_compile_options(bentley_ottmann    PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(gcd                PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(fraction           PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(point              PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(segment            PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(comparator         PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(read_data          PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(intersection       PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(begin_case         PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(end_case           PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(intersection_case  PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
    target_compile_options(main               PUBLIC SHELL:${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
endif()

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
