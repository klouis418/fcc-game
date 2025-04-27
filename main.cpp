#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include <iostream>
#include <vector>

struct FloatPairHash {
    std::size_t operator()(const std::pair<float, float>& key) const {
        auto h1 = std::hash<float>{}(key.first);
        auto h2 = std::hash<float>{}(key.second);
        return h1 ^ (h2 << 1); // Combines the two hashes
    }
};

sf::Vector2f vTileSize = {64, 32};
sf::Vector2f vWorldSize = {40, 40};
sf::Vector2f vOrigin = {14.5, 1};

std::unordered_map<std::pair<float, float>, int, FloatPairHash> pWorld;
std::unordered_map<std::pair<float, float>, sf::Vector2f, FloatPairHash> tilePositions;


sf::Vector2f ToScreen(float x, float y) {
    return sf::Vector2f {
        (vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
        (vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2)
    };
};


sf::Texture tileTexture; 
sf::Texture treeTexture;
sf::Texture jeffersonTexture;
sf::Texture linganoreTexture;

bool loadTextures() {
    bool tileLoad = tileTexture.loadFromFile("assets/tile.png"); 
    bool treeLoad = treeTexture.loadFromFile("assets/tree.png");
    bool jeffersonLoad = jeffersonTexture.loadFromFile("assets/jefferson.png");
    bool linganoreLoad = linganoreTexture.loadFromFile("assets/linganore.png");
    return tileLoad && treeLoad;
}

std::vector<sf::Sprite> tiles;
std::vector<sf::Sprite> trees;
std::vector<sf::Sprite> jeffersons;
std::vector<sf::Sprite> linganores;

std::vector<std::pair<int, int>> treePositions = { {6, 7}, {1,1}, {10, 12}, {10, 13}, {28,28} };
std::vector<std::pair<int, int>> jeffersonPositions = { {15, 16}};
std::vector<std::pair<int, int>> linganorePositions = { {23, 16}};

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "FCC Game!");
    window.setFramerateLimit(144);

    if (!loadTextures()) return -1; 

    // grid dimensions loop, assigning texture to Sprite
    for (float y = 0; y < vWorldSize.y; y++) {
        for (float x = 0; x < vWorldSize.x; x++) {
            sf::Sprite tile(tileTexture);
            sf::Vector2f vWorld = ToScreen(x, y);
            tile.setPosition(vWorld);
            tiles.push_back(tile);

            tilePositions[{x, y}] = vWorld;
        
           for (auto& pos : treePositions) {
                float x = static_cast<float>(pos.first);
                float y = static_cast<float>(pos.second);

             if (tilePositions.find({x, y}) != tilePositions.end()) {
                    sf::Sprite tree(treeTexture);
                    sf::Vector2f basePos = tilePositions[{x, y}];
                    sf::Vector2f adjusted_position(
                    basePos.x,
                    basePos.y - (treeTexture.getSize().y - vTileSize.y));
                    tree.setPosition(adjusted_position);
                    trees.push_back(tree);
                }
            }

            for (auto& pos : jeffersonPositions) {
                float x = static_cast<float>(pos.first);
                float y = static_cast<float>(pos.second);

             if (tilePositions.find({x, y}) != tilePositions.end()) {
                    sf::Sprite jefferson(jeffersonTexture);
                    sf::Vector2f basePos = tilePositions[{x, y}];
                    sf::Vector2f adjusted_position(
                    basePos.x,
                    basePos.y - (jeffersonTexture.getSize().y - vTileSize.y));
                    jefferson.setPosition(adjusted_position);
                    jeffersons.push_back(jefferson);
                }
            }

            for (auto& pos : linganorePositions) {
                float x = static_cast<float>(pos.first);
                float y = static_cast<float>(pos.second);

             if (tilePositions.find({x, y}) != tilePositions.end()) {
                    sf::Sprite linganore(linganoreTexture);
                    sf::Vector2f basePos = tilePositions[{x, y}];
                    sf::Vector2f adjusted_position(
                    basePos.x,
                    basePos.y - (linganoreTexture.getSize().y - vTileSize.y));
                    linganore.setPosition(adjusted_position);
                    linganores.push_back(linganore);
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

        for (auto& jefferson : jeffersons) {
            window.draw(jefferson);
        }

        for (auto& linganore : linganores) {
            window.draw(linganore);
        }
        
        sf::Font font("assets/Arial.ttf");
        if (!font.openFromFile("assets/Arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        for (auto& tilePosition : tilePositions) {
            sf::Text text(font); // Associate the font with the text
            text.setString("Tile Position"); // Set the displayed string
            text.setCharacterSize(12);  
            text.setFillColor(sf::Color::Red);

            // Display the tile coordinates as text
            std::pair<float, float> coords = tilePosition.first;
            std::string positionText = "(" + std::to_string((int)coords.first) + "," + std::to_string((int)coords.second) + ")";
            text.setString(positionText);

            // Position the text over the tile
            text.setPosition(tilePosition.second);
            window.draw(text);
        
        }
    
        window.display();
    }
    return 0;
}

