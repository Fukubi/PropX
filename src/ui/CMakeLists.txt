add_library(ui login_window.cpp)

target_include_directories(ui PUBLIC .)
target_link_directories(ui PRIVATE .)
target_link_libraries(ui PUBLIC Qt6::Widgets)

target_link_libraries(PropX PUBLIC ui)