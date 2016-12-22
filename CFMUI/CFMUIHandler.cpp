//
// Created by mohsen on 12/22/16.
//

#include "CFMUIHandler.h"

#include <X11/Xatom.h>
#include <X11/Xlib.h>

namespace {

    CFMUIHandler *g_instance = NULL;

}

CFMUIHandler::CFMUIHandler() : isClosing(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

CFMUIHandler::~CFMUIHandler() {
    g_instance = NULL;
}

CFMUIHandler *CFMUIHandler::GetInstance() {
    return g_instance;
}

void CFMUIHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) {

    CEF_REQUIRE_UI_THREAD();
    std::string titleStr(title);

    // Retrieve the X11 display shared with Chromium.
    ::Display* display = cef_get_xdisplay();
    DCHECK(display);

    // Retrieve the X11 window handle for the browser.
    ::Window window = browser->GetHost()->GetWindowHandle();
    DCHECK(window != kNullWindowHandle);

    // Retrieve the atoms required by the below XChangeProperty call.
    const char* kAtoms[] = {
            "_NET_WM_NAME",
            "UTF8_STRING"
    };
    Atom atoms[2];
    int result = XInternAtoms(display, const_cast<char**>(kAtoms), 2, false,
                              atoms);
    if (!result)
        NOTREACHED();

    // Set the window title.
    XChangeProperty(display,
                    window,
                    atoms[0],
                    atoms[1],
                    8,
                    PropModeReplace,
                    reinterpret_cast<const unsigned char*>(titleStr.c_str()),
                    titleStr.size());

    // TODO(erg): This is technically wrong. So XStoreName and friends expect
    // this in Host Portable Character Encoding instead of UTF-8, which I believe
    // is Compound Text. This shouldn't matter 90% of the time since this is the
    // fallback to the UTF8 property above.
    XStoreName(display, browser->GetHost()->GetWindowHandle(), titleStr.c_str());

}

void CFMUIHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browserList.push_back(browser);
}

bool CFMUIHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed destription of this
    // process.
    if (browserList.size() == 1) {
        // Set a flag to indicate that the window close should be allowed.
        isClosing = true;
    }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void CFMUIHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    // Remove from the list of existing browsers.
    BrowserList::iterator bit = browserList.begin();
    for (; bit != browserList.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browserList.erase(bit);
            break;
        }
    }

    if (browserList.empty()) {
        // All browser windows have closed. Quit the application message loop.
        CefQuitMessageLoop();
    }
}

void
CFMUIHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode,
                          const CefString &errorText, const CefString &failedUrl) {
    CEF_REQUIRE_UI_THREAD();

    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;

    // Display a load error message.
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
            "<h2>Failed to load URL " << std::string(failedUrl) <<
       " with error " << std::string(errorText) << " (" << errorCode <<
       ").</h2></body></html>";
    frame->LoadString(ss.str(), failedUrl);}

void CFMUIHandler::CloseAllBrowsers(bool force_close) {
    if (!CefCurrentlyOn(TID_UI)) {
        // Execute on the UI thread.
        CefPostTask(TID_UI,
                    base::Bind(&CFMUIHandler::CloseAllBrowsers, this, force_close));
        return;
    }

    if (browserList.empty())
        return;

    BrowserList::const_iterator it = browserList.begin();
    for (; it != browserList.end(); ++it)
        (*it)->GetHost()->CloseBrowser(force_close);
}

CefRefPtr<CefDisplayHandler> CFMUIHandler::GetDisplayHandler() {
    return this;
}

CefRefPtr<CefLifeSpanHandler> CFMUIHandler::GetLifeSpanHandler() {
    return this;
}

CefRefPtr<CefLoadHandler> CFMUIHandler::GetLoadHandler() {
    return this;
}

bool CFMUIHandler::IsClosing() const { return isClosing; }
