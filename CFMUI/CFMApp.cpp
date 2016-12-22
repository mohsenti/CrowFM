//
// Created by mohsen on 12/22/16.
//

#include "CFMApp.h"
#include "CFMUIHandler.h"

CefRefPtr<CefBrowserProcessHandler> CFMApp::GetBrowserProcessHandler() { return this; }

CFMApp::CFMApp() {

}

void CFMApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    // Information used when creating the native window.
    CefWindowInfo window_info;

#if defined(OS_WIN)
  window_info.SetAsPopup(NULL, "CFM");
#endif

    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<CFMUIHandler> handler(new CFMUIHandler());

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    std::string url;

    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    CefRefPtr<CefCommandLine> command_line =
            CefCommandLine::GetGlobalCommandLine();
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "file://../CFMHTMLUI/index.htm";

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                  browser_settings, NULL);
}
