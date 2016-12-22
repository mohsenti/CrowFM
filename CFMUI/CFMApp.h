//
// Created by mohsen on 12/22/16.
//

#ifndef CROWFM_CFMAPP_H
#define CROWFM_CFMAPP_H

#include "include/cef_app.h"

class CFMApp : public CefApp,
               public CefBrowserProcessHandler {
public:
    CFMApp();

    // CefApp methods:
    virtual CefRefPtr <CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CFMApp);
};


#endif //CROWFM_CFMAPP_H
