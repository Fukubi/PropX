add_library(user user.cpp)

target_include_directories(user PUBLIC .)
target_link_directories(user PRIVATE .)
target_link_libraries(user cryptography person)

target_link_libraries(PropX PUBLIC user)