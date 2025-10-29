import { argv, exit } from 'node:process';
import { join } from 'node:path';
import { readFileSync, writeFileSync } from 'node:fs';

const resourcesDir = argv[2];
const resourcesBinPath = argv[3];
const resourcesMapPath = argv[4];

if (!resourcesDir || !resourcesBinPath || !resourcesMapPath) {
    console.error('usage: bundle-resources <path> <bin> <map>');
    exit(1);
}

const bunnyPath = join(resourcesDir, 'bunny.png');
const bunny = readFileSync(bunnyPath);

writeFileSync(resourcesBinPath, bunny);
writeFileSync(
    resourcesMapPath,
    `#ifndef __RESOURCES_MAP_H
#define __RESOURCES_MAP_H

#define RESOURCES_MAP(X) \\
X(BUNNY, bunny, 0, 0, ${bunny.length})

#define RESOURCES_SIZE 1
#define RESOURCES_ID_MAX_SIZE 5

#endif`,
);
