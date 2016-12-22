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

    CefWindowInfo window_info;

#if defined(OS_WIN)
    window_info.SetAsPopup(NULL, "CFM");
#endif

    CefRefPtr<CFMUIHandler> handler(new CFMUIHandler());

    CefBrowserSettings browser_settings;

    std::string url;

    CefRefPtr<CefCommandLine> command_line =
            CefCommandLine::GetGlobalCommandLine();

    url = command_line->GetProgram();
    url = url.substr(0, url.find_last_of("/\\"));
    url = "file://" + url + "/../CFMHTMLUI/index.html";

    CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
                                  browser_settings, NULL);
}
