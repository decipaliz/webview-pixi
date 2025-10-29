#include "resources.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

resource_info_t resource_infos[] = {
#define X(NAME, ID, INDEX, START, SIZE) {#ID, START, SIZE},
    RESOURCES_MAP(X)
#undef X
};


static FILE *f_resources = NULL;

bool resources_init(void)
{
    f_resources = fopen(RESOURCES_PATH, "r");
    return f_resources != NULL;
}

void resources_deinit(void)
{
    if (f_resources != NULL)
        fclose(f_resources);
}

resource_id_t get_resource_id(const char *id)
{
#define X(NAME, ID, INDEX, START, SIZE) \
    if (strcmp(id, #ID) == 0)           \
        return RESOURCE_ID_##NAME;
    RESOURCES_MAP(X)
#undef X
    return RESOURCE_ID_UNKNOWN;
}

void *get_resource(resource_id_t id)
{
    if (id >= RESOURCE_ID_UNKNOWN || f_resources == NULL)
        return NULL;
    resource_info_t info = resource_infos[id];
    void *resource = malloc(info.size);
    fseek(f_resources, info.start, SEEK_SET);
    if (fread(resource, info.size, 1, f_resources) != 1) {
        free(resource);
        return NULL;
    }
    return resource;
}
