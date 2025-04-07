#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <cmath>


int main()
{
  //  sf::Font font (".vscode/arial(1).ttf");
  //  sf::Text text(font);
  //  text.setString("You are within the square!");
    sf::RenderWindow window(sf::VideoMode({500, 300}), "Mouse Click Practice");
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(100,100));
    square.setFillColor(sf::Color::Red);
    sf::Vector2f windowCenter(window.getSize().x / 2, window.getSize().y / 2);
    square.setPosition(windowCenter);


    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        
                sf::Vector2i position = sf:: Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                std:: cout <<" you just clicked the mouse! ";
                std:: cout<< "x position is: " << position.x << " y position is: " <<position.y << std::endl;
                if (position.x <= 350 && position.x >= 250 && position.y <= 250 && position.y >= 150){
                    std::cout <<"you are within the square";
                }
                {
                    /* code */
                }
                
            }
            /* code */
        }
        

        window.clear();
        window.draw(square);
       // window.draw(text);
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

