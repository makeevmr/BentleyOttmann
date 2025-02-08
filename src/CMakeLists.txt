add_subdirectory(gcd)
add_subdirectory(fraction)
add_subdirectory(point)
add_subdirectory(segment)
add_subdirectory(comparator)
add_subdirectory(read_data)
add_subdirectory(intersection)
add_subdirectory(bentley_ottmann)

add_library(main OBJECT main.cpp)

target_include_directories(main PUBLIC queue_item/include)
