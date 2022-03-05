#include <iostream>
#include <vector>

#include "mt.hpp"
#include "Manager.hpp"

using namespace std;

int main(int, char *)
{

    initMT();

    Manager *manager = Manager::getInstance();

    manager->managerInit();

    try
    {
        manager->simulationAnimee(1000, 40ms);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    delete manager;

    return 0;
}