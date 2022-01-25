#ifndef MEMOIRE_HPP
#define MEMOIRE_HPP

/**
 * @class Memoire
 * @brief Classe contenant les informations.
 */
class Memoire {

private:
    const int _tailleMemoire = 100;
    int _deplacement;
    int _renforcement;
    int _division;

public: 
   Memoire() {}

   // Getter
   int getDeplacement() {return _deplacement;}
   int getRenforcement() {return _renforcement;}
   int getDivision() {return _division;}

  

#endif