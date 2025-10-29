import { Texture } from 'pixi.js';
import { getResource } from './bindings';

export async function getTexture(resource: string): Promise<Texture> {
    return new Promise((resolve, reject) => {
        const image = new Image();
        image.addEventListener('load', () => resolve(Texture.from(image)));

        getResource(resource)
            .then((b64) => {
                image.src = 'data:image/png;base64,' + b64;
            })
            .catch(reject);
    });
}
