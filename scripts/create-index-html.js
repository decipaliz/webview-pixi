import { readFileSync, writeFileSync } from 'node:fs';
import { argv, exit } from 'node:process';
import { minify } from 'html-minifier-next';

const srcFilePath = argv[2];
const destFilePath = argv[3];

if (!srcFilePath || !destFilePath) {
    console.error('usage: create-index-html <src> <dest>');
    exit(1);
}

const srcFile = await minify(readFileSync(srcFilePath).toString(), {
    collapseWhitespace: true,
    removeComments: true,
    collapseBooleanAttributes: true,
    decodeEntities: true,
    minifyCSS: true,
    minifyJS: true,
    removeAttributeQuotes: true,
    removeRedundantAttributes: true,
    removeScriptTypeAttributes: true,
    removeStyleLinkTypeAttributes: true,
});

let destFile = `#ifndef __INDEX_HTML_H
#define __INDEX_HTML_H
const char *index_html = "`;

for (let byte of srcFile) {
    destFile += '\\x' + byte.charCodeAt(0).toString(16);
}

destFile += `";
#endif`;

writeFileSync(destFilePath, destFile);
