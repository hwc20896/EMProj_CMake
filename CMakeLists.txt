cmake_minimum_required(VERSION 3.22)
project(EMProj_CMake LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)
find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 23)

include_directories($ENV{VCPKG_ROOT}/installed/x64-mingw-dynamic/include)

qt_standard_project_setup()

qt_add_executable(EMProj_CMake
    main.cpp

    # CPPs
    src/cpp/widget_containers/mainwidget.cpp
    src/cpp/widgets/introwidget.cpp
    src/cpp/widgets/rulewidget.cpp
    src/cpp/widget_containers/managementwidget.cpp
    src/cpp/widgets/templatewidget.cpp
    src/cpp/widget_containers/outrowidget.cpp
    src/cpp/widgets/appinfowidget.cpp
    src/cpp/widgets/endwidget.cpp

    # Headers
    src/headers/widget_containers/mainwidget.hpp
    src/headers/widgets/introwidget.hpp
    src/headers/widgets/rulewidget.hpp
    src/headers/widget_containers/managementwidget.hpp
    src/headers/widgets/templatewidget.hpp
    src/headers/widget_containers/outrowidget.hpp
    src/headers/widgets/appinfowidget.hpp
    src/headers/widgets/endwidget.hpp

    # UIs
    src/ui/introwidget.ui
    src/ui/rulewidget.ui
    src/ui/managementwidget.ui
    src/ui/template.ui
    src/ui/appinfowidget.ui
    src/ui/endwidget.ui

    # Resources
    resources.qrc

    # Utility files
    src/cpp/utilities/fileread.cpp
    src/headers/utilities/fileread.hpp
    src/headers/utilities/defines.hpp
    src/headers/utilities/result.hpp
    src/headers/utilities/database.hpp
    src/cpp/utilities/database.cpp
    src/headers/utilities/questiondata.hpp

    # Element pairs
        # Mute Switch
        src/headers/elements/muteswitch.hpp
        src/cpp/elements/muteswitch.cpp

        # Option Button
        src/headers/elements/optionbutton.hpp
        src/cpp/elements/optionbutton.cpp

        # Gamemode Chooser
        src/headers/elements/gamemodechooser.hpp
        src/cpp/elements/gamemodechooser.cpp
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
        SQLite::SQLite3
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
