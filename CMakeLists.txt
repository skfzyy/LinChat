cmake_minimum_required(VERSION 3.20)
project(linChat)

set(CMAKE_CXX_STANDARD 14)
set(USE_UI 0)
set(SERVER_OR_CLIENT 1)

set(TEST_LinChat 1)


if (SERVER_OR_CLIENT)
    set(SERVER 1)
else ()
    set(CLient 1)
endif ()

add_subdirectory(./PyCom)


#区分操作系统
if (CMAKE_HOST_APPLE)
    message("the system is Macos")
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    message("the system is Linux")
    set(LINUX 1)
elseif(CMAKE_HOST_WIN32)
    message("the system is Win32")
    set(WIN32 1)
endif ()

# 设置环境相关变量
# 考虑后面引入QT来编辑界面
# 头文件
if (LINUX OR MACOS)
    message("配置Linux相关路径")
    set(USR_LOCAL_H /usr/local/include)
    set(PY_BIND_H /usr/local/Cellar/pybind11/2.7.0/include)
    message("include pybind")
    include_directories(${PY_BIND_H})
    #set CMAKE_PREFIX_PATH by Linux_QT_ENV.sh
endif ()


set(QT_FOLDER_PROJECT ${CMAKE_CURRENT_SOURCE_DIR}/LinChatUI)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(UTIL_SRC_H ${CMAKE_CURRENT_SOURCE_DIR}/Util/src)
set(UTIL_INCLUDE_H ${CMAKE_CURRENT_SOURCE_DIR}/Util/include)
find_package(Qt5Widgets REQUIRED)

include_directories(${UTIL_INCLUDE_H} ${USR_LOCAL_H})
aux_source_directory(${UTIL_SRC_H} UTIL_SRC_FILES)
aux_source_directory(${UTIL_INCLUDE_H} UTIL_INCLUDE_FILES)

if (TEST_LinChat)
    message("test the linChat Test")
    add_executable(linChat_Test main_test.cpp ${UTIL_INCLUDE_FILES} ${UTIL_SRC_FILES})
    target_link_libraries(linChat_Test "-framework Python")
    target_link_libraries(linChat_Test pycom)
else ()
    if (USE_UI)
        message("test ui")
        aux_source_directory(${QT_FOLDER_PROJECT} UI_FILES)
        add_executable(linChat ${QT_FOLDER_PROJECT}/main.cpp ${UI_FILES} ${UTIL_INCLUDE_FILES} ${UTIL_SRC_FILES})
        target_link_libraries(linChat Qt5::Widgets)
    else ()
        message("use console")
        if (SERVER)
            add_executable(linChat_Console_Server main_server.cpp ${UTIL_INCLUDE_FILES} ${UTIL_SRC_FILES})
        else ()
            #        add_executable(linChat_Test main_test.cpp)
            add_executable(linChat_Console_Client main_client.cpp ${UTIL_INCLUDE_FILES} ${UTIL_SRC_FILES})
        endif ()
    endif ()
endif ()


#if (TEST_LinChat)
#    message("test the linChat Test")
#    add_executable(linChat_Test main_test.cpp)
#endif ()
