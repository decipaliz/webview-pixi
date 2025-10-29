#ifndef __RESOURCES_H
#define __RESOURCES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>

#include "resources-map.h"

typedef enum {
#define X(NAME, ID, INDEX, START, SIZE) RESOURCE_ID_##NAME = INDEX,
    RESOURCES_MAP(X)
#undef X
    RESOURCE_ID_UNKNOWN,
} resource_id_t;

typedef struct resource_info_s resource_info_t;

struct resource_info_s {
    const char *name;
    size_t start;
    size_t size;
};

#define RESOURCES_PATH "resources.bin"

bool resources_init(void);
void resources_deinit(void);

extern resource_info_t resource_infos[RESOURCES_SIZE];

resource_id_t get_resource_id(const char *id);
void *get_resource(resource_id_t id);

#ifdef __cplusplus
}
#endif

#endif /* __RESOURCES_H */
