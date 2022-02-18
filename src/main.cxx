#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

#include "Manager.hpp"

using namespace std;

int main()
{

    // Agent agent0Bleu{2, 2, EQUIPE::BLEU};
    // Agent agent0Rouge{4, 4, EQUIPE::ROUGE};

    // Manager manager{agent0Bleu, agent0Rouge};

    // manager.afficherCarte();
    // for (int i = 0; i < 10; ++i)
    // {
    //     system("clear");
    //     manager.tour();
    //     // manager.afficherCarte();
    //     std::this_thread::sleep_for(100ms);
    // }
    // // manager.afficherCarte();

    sf::RenderWindow window(sf::VideoMode(900, 700), "SFML works!");
    sf::Event event;

    sf::CircleShape shape(100.f, 6);
    shape.setPosition(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {

        if (event.type == sf::Event::Closed)
            window.close();

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}