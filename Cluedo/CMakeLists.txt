cmake_minimum_required(VERSION 3.8)

project(Cluedo LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

IF (WIN32)
    # This you might change in order to find QT package successfully
    set(CMAKE_PREFIX_PATH D:\\Programme\\Qt\\Qt5.10.1\\5.10.1\\msvc2017_64\\lib\\cmake)
ENDIF()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/UI ${PROJECT_SOURCE_DIR}/Model ${PROJECT_SOURCE_DIR}/GameManager)

FILE(GLOB SOURCES_ALL_PLATFORM ${PROJECT_SOURCE_DIR}/UI/*.cpp ${PROJECT_SOURCE_DIR}/Model/*.cpp ${PROJECT_SOURCE_DIR}/GameManager/*.cpp ${PROJECT_SOURCE_DIR}/Utils/*.cpp main.cpp)
FILE(GLOB SOURCES_WIN_PLATFORM ${PROJECT_SOURCE_DIR}/Network/TcpWinSocketServer.cpp)

if (WIN32)
    set(SOURCES ${SOURCES_ALL_PLATFORM} ${SOURCES_WIN_PLATFORM})
ELSE()
    set(SOURCES ${SOURCES_ALL_PLATFORM})
ENDIF()

add_executable(${PROJECT_NAME} ${SOURCES})

IF (WIN32)
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ws2_32.lib)
ELSE()
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
ENDIF()

#Deploy QT DLLs to Output Dir
IF (WIN32)
    get_target_property(QtCore_location_Release Qt5::Core IMPORTED_LOCATION_RELEASE)
    get_target_property(QtQui_location_Release Qt5::Gui IMPORTED_LOCATION_RELEASE)
    get_target_property(QtWidgets_location_Release Qt5::Widgets IMPORTED_LOCATION_RELEASE)
    get_target_property(QtCore_location_Debug Qt5::Core IMPORTED_LOCATION_DEBUG)
    get_target_property(QtQui_location_Debug Qt5::Gui IMPORTED_LOCATION_DEBUG)
    get_target_property(QtWidgets_location_Debug Qt5::Widgets IMPORTED_LOCATION_DEBUG)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy ${QtCore_location_Release} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy ${QtQui_location_Release} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy ${QtWidgets_location_Release} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

        COMMAND ${CMAKE_COMMAND} -E copy ${QtCore_location_Debug} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy ${QtQui_location_Debug} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy ${QtWidgets_location_Debug} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Pics ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Pics
    )
ENDIF()