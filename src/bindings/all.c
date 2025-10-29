#include "bindings.h"
#include "webview/webview.h"

void bind_all(webview_t w)
{
    bind_get_resource(w);
    bind_get_resource_infos(w);
}
