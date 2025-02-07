add_subdirectory(bentley_ottmann)
add_subdirectory(read_data)
add_subdirectory(comparator)
add_subdirectory(find_intersection)
add_subdirectory(fraction)
add_subdirectory(gcd)
add_subdirectory(point)
add_subdirectory(segment)

add_library(main OBJECT main.cpp)

target_include_directories(main PUBLIC queue_item/include)
target_include_directories(main PUBLIC intersection_info/include)
