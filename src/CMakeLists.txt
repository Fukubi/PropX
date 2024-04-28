add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pqxx)

add_subdirectory(property)
add_subdirectory(cryptography)
add_subdirectory(user)
add_subdirectory(person)
add_subdirectory(purchase)
add_subdirectory(connector)