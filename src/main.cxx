#include <iostream>
#include <vector>

#include "mt.hpp"
#include "Manager.hpp"

using namespace std;

/*** Calcul intervale de confiance ***/
void confiance(vector<int> listCasesBleu,
               vector<int> listCasesRouge)
{
    int nbExp = (int)listCasesBleu.size();
    if (nbExp != (int)listCasesRouge.size())
        cerr << "Erreur pas le meme nb de tour entre les listes" << endl;

    double moyenneCasesBleu = 0.;
    double moyenneCasesRouge = 0.;

    for (int i = 0; i < nbExp; i++)
    {
        moyenneCasesBleu += listCasesBleu[i];
        moyenneCasesRouge += listCasesRouge[i];
    }
    moyenneCasesBleu /= nbExp;
    moyenneCasesRouge /= nbExp;

    // Calcul de S²(n)
    double s_n_carre_Bleu = 0;
    double s_n_carre_Rouge = 0;
    for (int k = 0; k < nbExp; k++)
    {
        s_n_carre_Bleu += (listCasesBleu[k] - moyenneCasesBleu) * (listCasesBleu[k] - moyenneCasesBleu);
        s_n_carre_Rouge += (listCasesRouge[k] - moyenneCasesRouge) * (listCasesRouge[k] - moyenneCasesRouge);
    }
    s_n_carre_Bleu /= nbExp - 1;
    s_n_carre_Rouge /= nbExp - 1;

    // Calcul du rayon de confiance
    double tab_t_n_1[6] = {2.228, 2.086, 2.042, 2.021, 2.000, 1.980}; // n = 10, 20, 30, 40, 80, 120

    double t_n_1;

    switch (nbExp)
    {
    case 10:
        t_n_1 = tab_t_n_1[0];
        break;
    case 20:
        t_n_1 = tab_t_n_1[1];
        break;
    case 30:
        t_n_1 = tab_t_n_1[2];
        break;
    case 40:
        t_n_1 = tab_t_n_1[3];
        break;
    case 80:
        t_n_1 = tab_t_n_1[4];
        break;
    case 120:
        t_n_1 = tab_t_n_1[5];
        break;
    default:
        std::cout << "Nb experience ne correspond pas avec les valeurs de tn-1,1-a/2";
        break;
    }
    double rBleu = t_n_1 * sqrt(s_n_carre_Bleu / nbExp);
    double rRouge = t_n_1 * sqrt(s_n_carre_Rouge / nbExp);

    double ecartEquipe = fabs(moyenneCasesBleu - moyenneCasesRouge);

    printf("\nPour %d simulations\n", nbExp);
    printf("Sur une carte hexagonale de %d par %d\n", TAILLE, TAILLE);

    std::cout << "Ecart moyen du nombre de cases capturees entre les deux equipes : " << ecartEquipe << endl
         << endl;

    printf("\nIntervale de confiance a 95%% du nombres de cases capturees par equipe :\n\n");

    std::cout << "\033[34m"; // Bleu
    printf("BLEU :  [ %.2lf - %.2lf; %.2lf + %.2lf ] ", moyenneCasesBleu, rBleu, moyenneCasesBleu, rBleu);
    printf("=> [ %.2lf ; %.2lf ]\n", moyenneCasesBleu - rBleu, moyenneCasesBleu + rBleu);

    std::cout << "\033[31m"; // Rouge
    printf("ROUGE : [ %.2lf - %.2lf; %.2lf + %.2lf ] ", moyenneCasesRouge, rRouge, moyenneCasesRouge, rRouge);
    printf("=> [ %.2lf ; %.2lf ]\n", moyenneCasesRouge - rRouge, moyenneCasesRouge + rRouge);

    std::cout << "\033[0m"; // Reset;
}

int main(int, char **)
{

    initMT();
    vector<int> listCasesCaptureesBleu;
    vector<int> listCasesCaptureesRouge;

    int n = 120;

    Manager *manager = Manager::getInstance();
    int nbCasesBleu, nbCasesRouge;
    int sumCasesBleu = 0;
    int sumCasesRouge = 0;

    // affichage d'une expérience pour voir le comportement
    manager->simulationAnimee(1000, 50ms);

    // affichage des stats pour 'n' répétitions de l'expérience
    try
    {
        for (int k = 0; k < n; ++k)
        {
            // manager->simulationAnimee(100, 40ms);
            manager->simulation(1000);
            manager->getCarte().compterStatCases(nbCasesBleu, nbCasesRouge);
            // std::cout << "cases bleu : " << nbCasesBleu << endl;
            // std::cout << "cases rouge : " << nbCasesRouge << endl;

            listCasesCaptureesBleu.push_back(nbCasesBleu);
            listCasesCaptureesRouge.push_back(nbCasesRouge);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }


    confiance(listCasesCaptureesBleu, listCasesCaptureesRouge);

    delete manager;

    return 0;
}