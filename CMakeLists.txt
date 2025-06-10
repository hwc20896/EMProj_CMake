cmake_minimum_required(VERSION 3.22)
project(EMProj_CMake LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia Sql)

set(CMAKE_CXX_STANDARD 23)

qt_standard_project_setup()

qt_add_executable(EMProj_CMake
    WIN32 MACOSX_BUNDLE
        main.cpp

        # CPPs
        src/cpp/mainwidget.cpp
        src/cpp/introwidget.cpp
        src/cpp/rulewidget.cpp

        # Headers
        src/headers/mainwidget.hpp
        src/headers/introwidget.hpp
        src/headers/rulewidget.hpp

        # UIs
        src/ui/introwidget.ui
        src/ui/rulewidget.ui
)

set_target_properties(EMProj_CMake PROPERTIES
    AUTOUIC ON
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    AUTORCC ON
)

target_link_libraries(EMProj_CMake
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        Qt::Sql
)

target_include_directories(EMProj_CMake
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
)

include(GNUInstallDirs)

install(TARGETS EMProj_CMake
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET EMProj_CMake
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
