cmake_minimum_required(VERSION 3.6)
project(CrowFM)

# Determine the platform.
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOSX 1)
    set(OS_POSIX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    set(OS_POSIX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
endif ()

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(SOURCE_FILES main.cpp CFMCore/CFMCore.cpp CFMCore/CFMCore.h CFMCore/CFMCoreTypes.h CFMCore/Gtk/CFMGtkCore.cpp CFMCore/CFMInterfaces.h CFMCore/Gtk/CFMGtkMount.cpp CFMCore/Gtk/CFMGtkMount.h CFMCore/Gtk/CFMGtkDrive.cpp CFMCore/Gtk/CFMGtkDrive.h CFMCore/Gtk/CFMGtkVolume.cpp CFMCore/Gtk/CFMGtkVolume.h)
add_executable(CrowFM ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
target_link_libraries(CrowFM ${GTK3_LIBRARIES})

find_package(GIO REQUIRED)
if (GIO_FOUND)
    include_directories(${GIO_INCLUDE_DIR})
    target_link_libraries(CrowFM ${GIO_LIBRARIES})
endif (GIO_FOUND)

find_package(X11 REQUIRED)
if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(CrowFM ${X11_LIBRARIES})
endif (X11_FOUND)