add_library(person person.cpp)

target_include_directories(person PUBLIC .)
target_link_directories(person PRIVATE .)

target_link_libraries(PropX PUBLIC person)