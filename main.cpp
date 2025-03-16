#include <SFML/Graphics.hpp>
#include <vector>

const int TILE_WIDTH = 64; // tile size
const int TILE_HEIGHT = 32;

const int MAP_WIDTH = 13;  // number of tiles in grid
const int MAP_HEIGHT = 10;

const int ORIGIN_X = 13;  // tilemap offset
const int ORIGIN_Y = 10;

sf::Texture tileTexture;  

bool loadTextures() {
    return tileTexture.loadFromFile("tile.png"); 
}

// convert  grid coordinates into screen pixel coordinates
sf::Vector2f toScreen(int x, int y) {
    return sf::Vector2f(
        (ORIGIN_X * TILE_WIDTH) + (x - y) * (TILE_WIDTH / 2),
        (ORIGIN_Y * TILE_HEIGHT) + (x + y) * (TILE_HEIGHT / 2)
    );
}

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Isometric Grid");
    window.setFramerateLimit(144);

    if (!loadTextures()) return -1; 

    // vector stores Sprite objecs(each tile)
    std::vector<sf::Sprite> tiles;

    // grid dimensions loop, assigning texture to Sprite
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            sf::Sprite tile(tileTexture);

            // set sprite position in isometric layout 
            sf::Vector2f screenPos = toScreen(x, y);
            tile.setPosition(screenPos);
            
            // store tile in vector
            tiles.push_back(tile);
        }
    }

    // game loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Green);

        // loop through each Sprite and render to screen
        for (auto& tile : tiles) {
            window.draw(tile);
        }

        window.display();
    }

    return 0;
}
