#include <iostream>
#include <vector>

#include "mt.hpp"
#include "Manager.hpp"

using namespace std;

int main(int, char *)
{

    initMT();

    Manager *manager = Manager::getInstance();

    try
    {
        manager->simulationAnimee(10, 40ms);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    int a, b;
    manager->afficherCarte();
    manager->getCarte().compterStatCases(a, b);
    cout << "cases bleu : " << a << endl;
    cout << "cases rouge : " << b << endl;

    delete manager;

    return 0;
}