find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(PropX
    ui/login_window.cpp
    ui/home_window.cpp
    ui/create_property.cpp
    ui/login-window.ui
    ui/home-window.ui
    ui/create-property.ui
    main.cpp
)

target_include_directories(PropX PUBLIC ui)

target_link_libraries(PropX PRIVATE Qt6::Widgets)

add_subdirectory(property)
add_subdirectory(cryptography)
add_subdirectory(user)
add_subdirectory(person)
add_subdirectory(purchase)
add_subdirectory(connector)
# add_subdirectory(ui)