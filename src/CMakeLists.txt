add_subdirectory(gcd)
add_subdirectory(fraction)
add_subdirectory(point)
add_subdirectory(segment)
add_subdirectory(comparator)
add_subdirectory(read_data)
add_subdirectory(intersection)
add_subdirectory(case_handlers)

add_library(main OBJECT main.cpp)
add_library(generate_data OBJECT generate_data.cpp)

target_include_directories(main PUBLIC queue_item/include)


list(APPEND GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS
    -DNDEBUG
    -O2
)

list(APPEND GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-promo
    -g
)

if(CMAKE_BUILD_TYPE STREQUAL CustomRelease)
    message(STATUS "CustomRelease BUILD TYPE")
    foreach(target IN ZIP_LISTS TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()

if(CMAKE_BUILD_TYPE STREQUAL CustomDebug)
    message(STATUS "CustomDebug BUILD TYPE")
    foreach(target IN ZIP_LISTS TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()
