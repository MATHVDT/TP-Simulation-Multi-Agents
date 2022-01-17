#ifndef CARTE_HPP
#define CARTE_HPP

const int taille = 10;

class Carte
{
    int _grille[taille][taille];

    public:
        Carte();
        void AfficherCarte();
        void ChangerCase(int i, int j, int val);
};

#endif