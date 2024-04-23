add_library(property property.cpp)

target_include_directories(property PUBLIC .)
target_link_directories(property PUBLIC .)

target_link_libraries(${PROJECT_NAME} property)