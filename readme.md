# CrowFM

## What's this ?

CrowFM is a cross platform file manager.

##How to build
**note : currently only linux os is supported.**

1 - Download Chromium Embedded Framework(CEF) and build it

2 - Copy CEF Resources directory to CEFModule
 
3 - Copy Release/*.* to OS directory

**note : OS directory name must be** 
* **windows for Windows**
* **linux for linux**
* **macos for MacOS**

4 - Copy libcef_dll_wrapper to OS directory
 
5 - Copy include directory to CEFModule

6 - Using cmake to generate Makefiles

7 - Using make to make executable

