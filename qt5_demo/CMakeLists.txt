project(qt5_demo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(amazing_cpp REQUIRED)

add_executable(
    ${PROJECT_NAME}_test
    unit_test.cpp
    hello_world.cpp
    choose_file_test.cpp
    choose_file_process_window.cpp
    hello_qt_button.cpp
    hello_qt_text.cpp
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gmock Qt5::Widgets amazing_cpp::amazing_cpp)


add_library(
    ${PROJECT_NAME}
    choose_file_process_window.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets amazing_cpp::amazing_cpp)

# include cmake modules for later use
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# basic install and generation of targets files
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# installation of target files
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# install config files(and installation?)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.cmake.in
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# generate ConfigVersion file
write_basic_package_version_file(
    ${PROJECT_NAME}-config-version.cmake
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

# install Config and ConfigVersion files
install(FILES
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES "${PROJECT_SOURCE_DIR}/choose_file_process_window.h" DESTINATION include/${PROJECT_NAME})