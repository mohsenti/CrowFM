//
// Created by mohsen on 12/22/16.
//

#ifndef CROWFM_CFMUIHANDLER_H
#define CROWFM_CFMUIHANDLER_H

#include <include/cef_client.h>
#include <include/base/cef_bind.h>
#include <include/cef_app.h>
#include <include/wrapper/cef_closure_task.h>
#include <include/wrapper/cef_helpers.h>

#include <list>

using namespace std;

class CFMUIHandler : public CefClient,
                     public CefDisplayHandler,
                     public CefLifeSpanHandler,
                     public CefLoadHandler {
public:
    CFMUIHandler();

    virtual ~CFMUIHandler();

    static CFMUIHandler *GetInstance();

    // CefClient methods:
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                               const CefString &title) OVERRIDE;

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             ErrorCode errorCode,
                             const CefString &errorText,
                             const CefString &failedUrl) OVERRIDE;

    // Request that all existing browser windows close.
    void CloseAllBrowsers(bool force_close);

    bool IsClosing() const;

private:
    // List of existing browser windows. Only accessed on the CEF UI thread.
    typedef list <CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browserList;

    bool isClosing;

    // Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(CFMUIHandler);

};


#endif //CROWFM_CFMUIHANDLER_H
