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
sf::Vector2f vWorldSize = {29, 29};
sf::Vector2f vOrigin = {14.5, 1};

std::unordered_map<std::pair<float, float>, sf::Vector2f, FloatPairHash> tilePositions;


sf::Vector2f ToScreen(float x, float y) {
    return sf::Vector2f {
        (vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
        (vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2)
    };
};


sf::Texture tileTexture; 
sf::Texture treeTexture;
sf::Texture buildingTexture;

bool loadTextures() {
    bool tileLoad = tileTexture.loadFromFile("assets/tile.png"); 
    bool treeLoad = treeTexture.loadFromFile("assets/tree.png");
    bool buildingLoad = buildingTexture.loadFromFile("assets/building.png");
    return tileLoad && treeLoad;
}

std::vector<sf::Sprite> tiles;
std::vector<sf::Sprite> trees;
std::vector<sf::Sprite> buildings;

std::vector<std::pair<int, int>> treePositions = { {0, 0}, {1,1}, {10, 12}, {10, 13}, {28,28} };
std::vector<std::pair<int, int>> buildingPositions = { {11, 12}, {12, 11}, {13, 11}, {28, 0}};

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

            for (auto& pos : buildingPositions) {
                float x = static_cast<float>(pos.first);
                float y = static_cast<float>(pos.second);

             if (tilePositions.find({x, y}) != tilePositions.end()) {
                    sf::Sprite building(buildingTexture);
                    sf::Vector2f basePos = tilePositions[{x, y}];
                    sf::Vector2f adjusted_position(
                    basePos.x,
                    basePos.y - (buildingTexture.getSize().y - vTileSize.y));
                    building.setPosition(adjusted_position);
                    buildings.push_back(building);
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

        for (auto& building : buildings) {
            window.draw(building);
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


