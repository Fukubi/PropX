add_library(database-connector database-connector.cpp)

target_include_directories(database-connector PUBLIC .)
target_link_directories(database-connector PRIVATE .)
target_link_libraries(database-connector pqxx spdlog person property user purchase)

target_link_libraries(${PROJECT_NAME} database-connector)