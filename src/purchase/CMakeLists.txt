add_library(purchase purchase.cpp)

target_include_directories(purchase PUBLIC .)
target_link_directories(purchase PRIVATE .)
target_link_libraries(purchase property user)

target_link_libraries(${PROJECT_NAME} purchase)