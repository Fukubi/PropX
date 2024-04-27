add_library(cryptography cryptography.cpp)

target_include_directories(cryptography PUBLIC .)
target_link_directories(cryptography PRIVATE .)
target_link_libraries(cryptography bcrypt)

target_link_libraries(${PROJECT_NAME} cryptography)