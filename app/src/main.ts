import './style.css';
import { Application, Container, Sprite } from 'pixi.js';
import { handleResize } from './resize';
import { getTexture } from './get-texture';

(async () => {
    const canvas = document.getElementById('canvas') as HTMLCanvasElement;

    const app = new Application();
    await app.init({ view: canvas });

    const container = new Container();

    app.stage.addChild(container);

    // Load the bunny texture
    const texture = await getTexture('bunny');

    // Create a 5x5 grid of bunnies in the container
    for (let i = 0; i < 25; i++) {
        const bunny = new Sprite(texture);

        bunny.x = (i % 5) * 40;
        bunny.y = Math.floor(i / 5) * 40;
        container.addChild(bunny);
    }

    // Move the container to the center
    container.x = app.screen.width / 2;
    container.y = app.screen.height / 2;

    // Center the bunny sprites in local container coordinates
    container.pivot.x = container.width / 2;
    container.pivot.y = container.height / 2;

    // Listen for animate update
    app.ticker.add((time) => {
        // Continuously rotate the container!
        // * use delta to create frame-independent transform *
        container.rotation -= 0.01 * time.deltaTime;
    });

    handleResize();
})();
