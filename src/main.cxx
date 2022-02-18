#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Manager.hpp"

using namespace std;

int main()
{
    const int largeurWindow = 1000;
    const int hauteurWindow = 700;

    sf::RenderWindow window(sf::VideoMode(largeurWindow, hauteurWindow), "SFML works!");
    sf::Event event;

    Agent agent0Bleu{2, 2, EQUIPE::BLEU};
    Agent agent0Rouge{4, 4, EQUIPE::ROUGE};
    Manager manager{agent0Bleu, agent0Rouge};

    for (int i = 0; i < 50; ++i)
    {
        // system("clear");
        manager.tour();

        window.clear(sf::Color::Black);
        // manager.afficherCarte();
        manager.afficherSfml(window, largeurWindow, hauteurWindow);

        window.display();
        std::this_thread::sleep_for(50ms);
    }
    // manager.afficherCarte();

    while (window.isOpen())
    {

        if (event.type == sf::Event::Closed)
            window.close();
    }

    return 0;
}