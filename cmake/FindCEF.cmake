UNSET(CEF_INCLUDE_DIRECTORY CACHE)
UNSET(CEF_LIBRARIES CACHE)

SET(CEF_PATHS "/home/mohsen/Desktop/Workstation/cef_binary_3.2623.1390.g44fcb48_linux64")

find_path(CEF_INCLUDE_DIRECTORY
        "include/cef_app.h"
        PATHS ${CEF_PATHS})


find_library(CEF_LIBRARY libcef.so PATHS "${CEF_INCLUDE_DIRECTORY}/Release")

#libcef_dll_wrapper.a

find_library(CEF_WRAPPER_LIBRARY libcef_dll_wrapper.a PATHS "${CEF_INCLUDE_DIRECTORY}/libcef_dll")

SET(CEF_LIBRARIES ${CEF_LIBRARY} ${CEF_WRAPPER_LIBRARY})

SET(CEF_RESOURCES_DIR "${CEF_INCLUDE_DIRECTORY}/Resources")

SET(CEF_FOUND 1)