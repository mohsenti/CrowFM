#include <iostream>

#include "CFMCore/CFMCoreTypes.h"
#include "CFMCore/CFMCore.h"

#include "CFMUI/CFMApp.h"

#include <X11/Xlib.h>

#include "include/base/cef_logging.h"

namespace {

    int XErrorHandlerImpl(Display *display, XErrorEvent *event) {
        LOG(WARNING)
        << "X error received: "
        << "type " << event->type << ", "
        << "serial " << event->serial << ", "
        << "error_code " << static_cast<int>(event->error_code) << ", "
        << "request_code " << static_cast<int>(event->request_code) << ", "
        << "minor_code " << static_cast<int>(event->minor_code);
        return 0;
    }

    int XIOErrorHandlerImpl(Display *display) {
        return 0;
    }

}  // namespace


int main(int argc, char *argv[]) {
//    CFMCore core;
//    CFMDeviceList mounts = core.GetDevices();
//    for (CFMDeviceList::iterator it = mounts.begin(); it != mounts.end(); it++) {
//        cout << (*it)->GetName() << endl;
//    }
//    return 0;

    CefMainArgs main_args(argc, argv);

    int exit_code = CefExecuteProcess(main_args, NULL, NULL);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    CefSettings settings;
    settings.single_process = True;

    CefRefPtr<CFMApp> app(new CFMApp);

    CefInitialize(main_args, settings, app.get(), NULL);

    CefRunMessageLoop();

    CefShutdown();

    return 0;

}