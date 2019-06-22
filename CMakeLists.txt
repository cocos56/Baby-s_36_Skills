#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Client)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/Connect.cpp
     Classes/ConnectServerScene.cpp
     Classes/CreateRoomScene.cpp
     Classes/GetRoomsScene.cpp
     Classes/JoinRoomScene.cpp
     Classes/NetworkBaseScene.cpp
     Classes/NetworkGameOverScene.cpp
     Classes/NetworkGameScene.cpp
     Classes/RoomsInfo.cpp
     Classes/SelectRoleScene.cpp
     Classes/SignInScene.cpp
     Classes/SignUpScene.cpp
     Classes/WaitingNetworkGameScene.cpp
     Classes/QuickEngine/QAnimate.cpp
     Classes/QuickEngine/QEditBox.cpp
     Classes/QuickEngine/QJson.cpp
     Classes/QuickEngine/QMenu.cpp
     Classes/QuickEngine/QMessageBox.cpp
     Classes/QuickEngine/QObject.cpp
     Classes/QuickEngine/QScene.cpp
     Classes/QuickEngine/QSprite.cpp
     Classes/QuickEngine/QString.cpp
     Classes/QuickEngine/QTMX.cpp
     Classes/Test/HelloWorldScene.cpp
     Classes/Test/HttpTest.cpp
     Classes/Test/PopAlertDialog.cpp
     Classes/Test/SignInSceneTest.cpp
     Classes/Test/SocketIOTestLayer.cpp
     Classes/Test/WebSocketTestLayer.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/Connect.h
     Classes/ConnectServerScene.h
     Classes/CreateRoomScene.h
     Classes/GetRoomsScene.h
     Classes/JoinRoomScene.h
     Classes/NetworkBaseScene.h
     Classes/NetworkGameOverScene.h
     Classes/NetworkGameScene.h
     Classes/QE.h
     Classes/RoomsInfo.h
     Classes/SelectRoleScene.h
     Classes/SignInScene.h
     Classes/SignUpScene.h
     Classes/WaitingNetworkGameScene.h
     Classes/QuickEngine/QAnimate.h
     Classes/QuickEngine/QDesignMode.h
     Classes/QuickEngine/QEditBox.h
     Classes/QuickEngine/QFileUtils.h
     Classes/QuickEngine/QJson.h
     Classes/QuickEngine/QLayer.h
     Classes/QuickEngine/QMenu.h
     Classes/QuickEngine/QMessageBox.h
     Classes/QuickEngine/QObject.h
     Classes/QuickEngine/QScene.h
     Classes/QuickEngine/QSprite.h
     Classes/QuickEngine/QString.h
     Classes/QuickEngine/QTMX.h
     Classes/QuickEngine/QType.h
     Classes/QuickEngine/QuickEngine.h
     Classes/Test/HelloWorldScene.h
     Classes/Test/HttpTest.h
     Classes/Test/PopAlertDialog.h
     Classes/Test/SignInSceneTest.h
     Classes/Test/SocketIOTestLayer.h
     Classes/Test/WebSocketTestLayer.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR}/..)
endif()

if(LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
