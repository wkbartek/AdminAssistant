cmake_minimum_required(VERSION 3.19)
project(AdminAssistant LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Test)

qt_standard_project_setup()

qt_add_executable(AdminAssistant
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(AdminAssistant
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS AdminAssistant
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET AdminAssistant
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

enable_testing()

qt_add_executable(AppTests tests.cpp)
target_link_libraries(AppTests PRIVATE Qt6::Core Qt6::Test)

add_test(NAME AppTests COMMAND AppTests)