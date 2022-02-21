cmake_minimum_required(VERSION 3.5)

project(GUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5Charts)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG beb9e98806bb84bcc130a2cebfbcbbc6ce62b335) # The commit hash for 1.7.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.10.5
)
FetchContent_MakeAvailable(json)


if(ANDROID)
  add_library(GUI SHARED
    main.cpp
    gui.cpp
    gui.h
    gui.ui
    dashboard.h
    dashboard.cpp
    dashboard.ui
    singup.h
    singup.cpp
    singup.ui
  )
else()
  add_executable(GUI
    main.cpp
    gui.cpp
    gui.h
    gui.ui
    dashboard.h
    dashboard.cpp
    dashboard.ui
    singup.h
    singup.cpp
    singup.ui
    transaction.cpp
    transaction.h
    statistic.cpp
    statistic.h
  )
endif()

target_link_libraries(GUI PRIVATE Qt5::Widgets)
target_link_libraries(GUI PRIVATE cpr::cpr)
target_link_libraries(GUI PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(GUI PRIVATE Qt5::Charts)
