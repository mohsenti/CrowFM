# CrowFM

## What's this ?

CrowFM is a cross platform file manager.

##How to build
**note : currently only linux os is supported.**

1 - Download Chromium Embedded Framework(CEF) and build it

2 - Create CEFModule directory in source
 
3 - Create OS directory in CEFModule

**note : OS directory name must be** 
* **windows for Windows**
* **linux for linux**
* **macos for MacOS**

4 - Copy CEF Resources directory to CEFModule
 
5 - Copy Release/*.* to OS directory

6 - Copy libcef_dll_wrapper to OS directory
 
7 - Copy include directory to CEFModule

8 - Copy macros.cmake to CEFModule

9 - Using cmake to generate Makefiles

10 - Using make to make executable

