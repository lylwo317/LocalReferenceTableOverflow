cmake_minimum_required(VERSION 3.6.0)
project(LocalRefLeak)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME lrtoverflow)#设置生成的so文件名，最后会生成libxxxx.so

include_directories(.)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Current platform: Linux ")

    FIND_PACKAGE(JNI REQUIRED)
    MESSAGE(STATUS "JNI INCLUDE DIR ${JNI_INCLUDE_DIRS}")

    INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})
    add_library(${TARGET_NAME} SHARED LRTOverflow.cpp)

    #设置相应的java项目存放so的路径。设置之后，会将so拷贝到${JAVA_PROJECT_LIBS_PATH}目录中
    #set(JAVA_PROJECT_LIBS_PATH /home/kevin/Workspace/IdeaProjects/JavaLearn/libs)

    if (JAVA_PROJECT_LIBS_PATH)#如何配置了调用该共享库的java项目路径，就执行拷贝共享库到java项目的操作。
        add_custom_command(TARGET ${TARGET_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo Copy file $<TARGET_FILE:${TARGET_NAME}> to ${JAVA_PROJECT_LIBS_PATH}
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${JAVA_PROJECT_LIBS_PATH})
    endif()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "Current platform: Android")
    add_library(${TARGET_NAME} SHARED LRTOverflow.cpp)
ENDIF()