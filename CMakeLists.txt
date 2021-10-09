cmake_minimum_required(VERSION 3.20)
project(linChat)

set(CMAKE_CXX_STANDARD 14)

#switch option
set(TEST_LinChat OFF)
set(USE_UI ON)
set(SERVER_OR_CLIENT ON)


# variable
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
message(${SOURCE_DIR})


if (SERVER_OR_CLIENT)
    set(SERVER ON)
else ()
    set(CLient ON)
endif ()


#区分操作系统
if (APPLE)
    set(MacOS ON)
    add_definitions(-DMACOS)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DLinux)
    set(Linux ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(Windows ON)
    add_definitions(-DWINDOWS)
endif()

if (MacOS)
    #do some macos setting
elseif(Linux)
    # do some linux setting
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# head files
include_directories(${SOURCE_DIR})

#src files
aux_source_directory(${SOURCE_DIR}/LinChatUI LinChatUI_FILES)
aux_source_directory(${SOURCE_DIR}/Util Util_FILES)


find_package(Qt5Widgets REQUIRED)

if (TEST_LinChat)
    # 测试用,编译main_test.cpp
    message("test the linChat Test")
    add_executable(linChat_Test main_test.cpp ${Util_FILES})
else ()
    if (USE_UI)
        message("test ui")
        # QT setting
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
        find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
        add_definitions(-DUSE_UI=true)

        add_executable(linChat ${LinChatUI_FILES} ${Util_FILES})
        target_link_libraries(linChat Qt5::Widgets Qt5::Core)
    else ()
        message("use console")
        if (SERVER)
            add_executable(linChat_Console_Server main_server.cpp ${Util_FILES})
        else ()
            #        add_executable(linChat_Test main_test.cpp)
            add_executable(linChat_Console_Client main_client.cpp ${Util_FILES})
        endif ()
    endif ()
endif ()
