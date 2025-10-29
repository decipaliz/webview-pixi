
#include "bindings.h"

#include "libbase64.h"
#include "resources-map.h"
#include "resources.h"
#include "webview/webview.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char resource_id_buf[RESOURCES_ID_MAX_SIZE + 1];
static void get_resource_cb(const char *id, const char *req, void *arg);
static void get_resource_infos_cb(const char *id, const char *req, void *arg);

void bind_get_resource(webview_t w)
{
    webview_bind(w, "_get_resource", get_resource_cb, w);
}

void bind_get_resource_infos(webview_t w)
{
    webview_bind(w, "_get_resource_infos", get_resource_infos_cb, w);
}

static void get_resource_cb(const char *id, const char *req, void *arg)
{
    webview_t w = arg;
    if (req[1] != '"') {
        webview_return(w, id, 0, "1");
        return;
    }

    const char *closing_quote = strchr(req + 2, '"');
    size_t size = closing_quote - (req + 2);
    memcpy(resource_id_buf, req + 2, size);
    resource_id_buf[size] = '\0';

    resource_id_t resource_id = get_resource_id(resource_id_buf);
    if (resource_id == RESOURCE_ID_UNKNOWN) {
        webview_return(w, id, 0, "2");
        return;
    }

    uint8_t *resource = get_resource(resource_id);
    if (resource == NULL) {
        webview_return(w, id, 0, "3");
        return;
    }

    resource_info_t info = resource_infos[resource_id];

    size_t result_size,
           result_capacity = (size_t)((double)info.size * 4.0 / 3.0) + 16;
    char *result = malloc(result_capacity * sizeof(char));
    if (result == NULL) {
        webview_return(w, id, 0, "4");
        return;
    }
    *result = '"';
    base64_encode((const char *)resource,
                  info.size,
                  result + 1,
                  &result_size,
                  0);
    *(result + result_size + 1) = '"';
    *(result + result_size + 2) = '\0';

    webview_return(w, id, 0, result);
    free(result);
}

static void get_resource_infos_cb(const char *id, const char *req, void *arg)
{
    (void)req;
    webview_t w = arg;
    size_t size = 0;
    char *result =
        malloc((sizeof("[]") +
                (sizeof("{\"index\":999999,\"name\":,\"start\":"
                        "18446744073709551615,\"size\":18446744073709551615}") *
                 RESOURCES_SIZE)) *
               sizeof(char));
    if (result == NULL) {
        webview_return(w, id, 0, "");
    }
    result[size++] = '[';

    for (size_t i = 0; i < RESOURCES_SIZE; ++i) {
        resource_info_t info = resource_infos[i];

        if (i != 0) {
            result[size++] = ',';
        }

        size += sprintf(result + size, 
                        "{\"index\":%lu,"
                        "\"name\":\"%s\","
                        "\"start\":%lu,"
                        "\"size\":%lu}",
                        i,
                        info.name,
                        info.start,
                        info.size);
    }

    result[size++] = ']';
    result[size] = '\0';

    webview_return(w, id, 0, result);
    free(result);
}
