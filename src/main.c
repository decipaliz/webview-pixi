#include "bindings.h"
#include "webview/webview.h"

#include "resources.h"
#include <stddef.h>
#include <stdio.h>

#include "index_html.h"

#ifdef NDEBUG
    #define USE_DEVTOOLS 0
#else
    #define USE_DEVTOOLS 1
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>

int WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPrevInst,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    (void)hInst;
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;
#else
int main(void)
{
#endif

    if (!resources_init()) {
        fputs("failed to initialize resources\n", stderr);
        return 1;
    }

    webview_t w = webview_create(USE_DEVTOOLS, NULL);
    webview_set_title(w, "webview + PixiJS");
    webview_set_size(w, 800, 600, WEBVIEW_HINT_FIXED);
    webview_set_html(w, index_html);
    bind_all(w);
    webview_run(w);
    webview_destroy(w);
    return 0;
}
