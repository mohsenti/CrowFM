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

set(SOURCE_FILES main.cpp CFMCore/CFMCore.cpp CFMCore/CFMCore.h CFMCore/CFMCoreTypes.h CFMCore/Gtk/CFMGtkCore.cpp CFMCore/CFMInterfaces.h CFMCore/Gtk/CFMGtkMount.cpp CFMCore/Gtk/CFMGtkMount.h CFMCore/Gtk/CFMGtkDrive.cpp CFMCore/Gtk/CFMGtkDrive.h CFMCore/Gtk/CFMGtkVolume.cpp CFMCore/Gtk/CFMGtkVolume.h CFMUI/CFMApp.cpp CFMUI/CFMApp.h CFMUI/CFMUIHandler.cpp CFMUI/CFMUIHandler.h)
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

include(CEFModule/macros.cmake)

SET(CEFModule "${CMAKE_SOURCE_DIR}/CEFModule")

include_directories("${CEFModule}")

if (OS_LINUX)
    # List of CEF binary files.
    set(CEF_BINARY_FILES
            chrome-sandbox
            libcef.so
            natives_blob.bin
            snapshot_blob.bin
            )

    # List of CEF resource files.
    set(CEF_RESOURCE_FILES
            cef.pak
            cef_100_percent.pak
            cef_200_percent.pak
            cef_extensions.pak
            devtools_resources.pak
            icudtl.dat
            locales
            )
    SET(CEF_RESOURCE_DIR "${CEFModule}/Resources")
    SET(CEF_BINARY_DIR "${CEFModule}/linux")

    # Executable target.
    find_library(CEF_LIB libcef.so PATHS ${CMAKE_BINARY_DIR})
    find_library(CEF_LIB_WRAPPER libcef_dll_wrapper.a PATHS "${CEF_BINARY_DIR}")
    target_link_libraries(CrowFM ${CEF_LIB} ${CEF_LIB_WRAPPER})

    # Set SUID permissions on the chrome-sandbox target.
    SET_LINUX_SUID_PERMISSIONS(CrowFM "${CMAKE_BINARY_DIR}/chrome-sandbox")
endif ()

# Copy binary and resource files to the target output directory.
COPY_FILES(CrowFM "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_BINARY_DIR}")
COPY_FILES(CrowFM "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_BINARY_DIR}")