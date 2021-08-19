cmake_minimum_required(VERSION 3.20)
project(linChat)

set(CMAKE_CXX_STANDARD 14)
set(USE_UI 1)
set(QT_FOLDER_PROJECT ${CMAKE_CURRENT_SOURCE_DIR}/LinChatUI)


#区分操作系统
if(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# 设置环境相关变量
# 考虑后面引入QT来编辑界面
# 头文件
if (LINUX AND MACOS)
    message("配置Linux相关路径")
    set(USR_LOCAL_H /usr/local/include)
#    set(CMAKE_PREFIX_PATH "/Users/shenhangke/tools/QT/5.15.2/clang_64/lib/cmake/")
endif ()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(UTIL_INCLUDE_H ./Util/include)
find_package(Qt5Widgets REQUIRED)


if (LINUX AND MACOS)
    message("配置Linux相关路径")
    set(USR_LOCAL_H /usr/local/include)
endif ()
include_directories(${UTIL_INCLUDE_H} ${USR_LOCAL_H})

if (USE_UI)
    message("test ui")
    aux_source_directory(${QT_FOLDER_PROJECT} UI_FILES)
    add_executable(linChat ${QT_FOLDER_PROJECT}/main.cpp ${UI_FILES})
else()
    message("use console")
    add_executable(linChat ${QT_FOLDER}/main.cpp)
endif ()

target_link_libraries(linChat Qt5::Widgets)
