export async function getResource(resource: string): Promise<string> {
    const res: 1 | 2 | 3 | 4 | string = await (window as any)._get_resource(
        resource,
    );

    if (res === 1) throw 'invalid input';
    if (res === 2) throw 'unknown resource id';
    if (res === 3) throw 'failed to get resource';
    if (res === 4) throw 'unable to convert to base64';

    return res;
}

export type ResourceInfo = {
    index: number;
    name: string;
    start: number;
    size: number;
};

let resourceInfos: ResourceInfo[] | undefined;

export async function getResourceInfos(): Promise<ResourceInfo[]> {
    if (resourceInfos === undefined) {
        resourceInfos = await (window as any)._get_resource_infos();

        if (resourceInfos === undefined) throw 'failed to get resource infos';
    }
    return resourceInfos;
}
