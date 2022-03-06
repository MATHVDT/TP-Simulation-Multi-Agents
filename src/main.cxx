#include <iostream>
#include <vector>

#include "mt.hpp"
#include "Manager.hpp"

using namespace std;

int main(int, char *)
{

    initMT();

    int n = 5;

    Manager *manager = Manager::getInstance();
    int nbCasesBleu, nbCasesRouge;
    int sumCasesBleu = 0;
    int sumCasesRouge = 0;

    try
    {
        for (int k = 0; k < n; ++k)
        {
            // manager->simulationAnimee(100, 40ms);
            manager->simulation(1000);
            manager->getCarte().compterStatCases(nbCasesBleu, nbCasesRouge);
            cout << "cases bleu : " << nbCasesBleu << endl;
            cout << "cases rouge : " << nbCasesRouge << endl;

            sumCasesBleu += nbCasesBleu;
            sumCasesRouge += nbCasesRouge;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    manager->afficherCarte();

    cout << endl;
    cout << "CASES BLEU " << sumCasesBleu / n << "  " << sumCasesBleu << endl;
    cout << "CASES ROUGE " << sumCasesRouge / n << "  " << sumCasesRouge << endl;

    delete manager;

    return 0;
}