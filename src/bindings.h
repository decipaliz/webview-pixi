#ifndef __BINDINGS_H
#define __BINDINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "webview/webview.h"

void bind_all(webview_t w);
void bind_get_resource(webview_t w);
void bind_get_resource_infos(webview_t w);

#ifdef __cplusplus
}
#endif

#endif /* __BINDINGS_H */
