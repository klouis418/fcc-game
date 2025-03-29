#include <SFML/Graphics.hpp>
#include <vector>

const int TILE_WIDTH = 64; // tile size
const int TILE_HEIGHT = 32;

const int MAP_WIDTH = 10;  // number of tiles in grid
const int MAP_HEIGHT = 10;

const int ORIGIN_X = 15;  // tilemap offset
const int ORIGIN_Y = 1;

sf::Texture tileTexture; 
sf::Texture treeTexture;

bool loadTextures() {
    bool tileLoaded = tileTexture.loadFromFile("tile.png"); 
    bool treeLoaded = treeTexture.loadFromFile("tree.png");
    return tileLoaded && treeLoaded;
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

    // vector stores Sprite objects
    std::vector<sf::Sprite> tiles;
    std::vector<sf::Sprite> trees;

    std::vector<std::pair<int, int>> treePositions = { {5, 2}, {8, 8}, {3, 4} };

    // grid dimensions loop, assigning texture to Sprite
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            sf::Sprite tile(tileTexture);
            sf::Vector2f screenPos = toScreen(x, y);
            tile.setPosition(screenPos);
            tiles.push_back(tile);

           for (auto& pos : treePositions) {
                if (pos.first == x && pos.second == y) {
                    sf::Sprite tree(treeTexture);
                    // Adjust the tree position to appear correctly on top of the tile
                    tree.setPosition(sf::Vector2f(screenPos.x, screenPos.y - 96)); // Adjust the -96 based on tree height
                    trees.push_back(tree);
                }
            }
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

        for (auto& tree : trees) {
            window.draw(tree);
        }

        window.display();
       
    }

    return 0;
}
