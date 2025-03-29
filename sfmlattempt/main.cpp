#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <cmath>


int main()
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Mouse Click Practice");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        
                sf::Vector2i position = sf:: Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                std:: cout <<" you just clicked the mouse! ";
            }
            /* code */
        }
        

        window.clear();
        window.draw(shape);
        window.display();
    }
}


// #include <SFML/Graphics.hpp>
// #include <iostream>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode({1020, 800}), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setRadius(200);
//     shape.setPosition({300,200});
//     shape.setFillColor(sf::Color::Red);

//     while (window.isOpen())
//     // sf::Event event;
//     {        
//         while (const std::optional event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();
//         }
//         // if (event.type == sf::Event::MouseButtonPressed)
//         // {
//             /* code */
//         }
//         sf::Vector2i position = sf::Mouse::getPosition(window) ;
//         std::cout << "x = " << position.x << ", y =" << position.y << '\n';

//         window.draw(shape);
//         window.display();
//     }

