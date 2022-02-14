/**
 * @file tests_catch.cpp
 * @brief Fichier contenant les tests unitaires.
 */
#include <fstream>
#include <iostream>

#include "catch.hpp"
#include "Agent.hpp"
#include "Memoire.hpp"
#include "Carte.hpp"


TEST_CASE("Test point")
{
  Point p1{4,5};
  Point p2{1,2};

 Point p3 =  p1 + p2;

  REQUIRE(p3.getX() == 5);
  REQUIRE(p3.getY() == 7);
}


TEST_CASE("Deplacement agent")
{
  Agent a{0, 0, EQUIPE::BLEU};

  SECTION("Deplacement Nord Ouest")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement ↖
    a.deplacer(DIRECTION::NORDOUEST);

    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == -1);
  }

  SECTION("Deplacement Ouest")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement ←
    a.deplacer(DIRECTION::OUEST);

    REQUIRE(a.getX() == -1);
    REQUIRE(a.getY() == 0);
  }

  SECTION("Deplacement Sud Ouest")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement ↙
    a.deplacer(DIRECTION::SUDOUEST);

    REQUIRE(a.getX() == -1);
    REQUIRE(a.getY() == 1);
  }

  SECTION("Deplacement Sud Est")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement ↘
    a.deplacer(DIRECTION::SUDEST);

    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 1);
  }

  SECTION("Deplacement Est")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement →
    a.deplacer(DIRECTION::EST);

    REQUIRE(a.getX() == 1);
    REQUIRE(a.getY() == 0);
  }

  SECTION("Deplacement Nord Est")
  {
    // Position (0,0)
    REQUIRE(a.getX() == 0);
    REQUIRE(a.getY() == 0);

    // Deplacement ↗
    a.deplacer(DIRECTION::NORDEST);

    REQUIRE(a.getX() == 1);
    REQUIRE(a.getY() == -1);
  }
}

TEST_CASE("Apprentissage mémoire")
{
  float eps = Memoire::getEpsilon();

  Memoire m1{EQUIPE::BLEU};
  Memoire m2{0.2, 0.2, 0.6, EQUIPE::BLEU};

  SECTION("Influence de 0.5")
  {
    // Vérification état de la mémoire
    REQUIRE(m1.getDivision() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(1. / 3.).epsilon(eps));

    REQUIRE(m2.getDivision() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getDeplacement() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getRenforcement() == Approx(0.6).epsilon(eps));

    // m1 apprend de m2 avec une influence de 0.5
    m1.apprentissage(0.5, m2);

    // Vérification de l'apprentissage
    REQUIRE(m1.getDivision() == Approx(0.267).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(0.267).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(0.467).epsilon(eps));

    // Vérifiaction que la mémoire de m2 n'a pas été altéré
    REQUIRE(m2.getDivision() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getDeplacement() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getRenforcement() == Approx(0.6).epsilon(eps));
  }

  SECTION("Influence de 1") // Pas possible d'avoir une influence >= 1
  {
    // Vérification état de la mémoire
    REQUIRE(m1.getDivision() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(1. / 3.).epsilon(eps));

    REQUIRE(m2.getDivision() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getDeplacement() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getRenforcement() == Approx(0.6).epsilon(eps));

    // m1 apprend de m2 avec une influence de 1
    m1.apprentissage(1, m2);

    // Vérification de l'apprentissage
    REQUIRE(m1.getDivision() == Approx(0.200).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(0.200).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(0.600).epsilon(eps));
  }

  SECTION("Influence de 0") // Pas possible d'avoir une influence <= 0
  {
    // Vérification état de la mémoire
    REQUIRE(m1.getDivision() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(1. / 3.).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(1. / 3.).epsilon(eps));

    REQUIRE(m2.getDivision() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getDeplacement() == Approx(0.2).epsilon(eps));
    REQUIRE(m2.getRenforcement() == Approx(0.6).epsilon(eps));

    // m1 apprend de m2 avec une influence de 0
    m1.apprentissage(0, m2);

    // Vérification de l'apprentissage
    REQUIRE(m1.getDivision() == Approx(0.3333).epsilon(eps));
    REQUIRE(m1.getDeplacement() == Approx(0.333).epsilon(eps));
    REQUIRE(m1.getRenforcement() == Approx(0.333).epsilon(eps));
  }
}

TEST_CASE("Partage de la mémoire à un voisinage")
{
  float eps = Memoire::getEpsilon();

  EQUIPE allies = EQUIPE::BLEU;
  EQUIPE ennemis = EQUIPE::ROUGE;

  Agent agentCentral{0, 0, allies};

  Agent *allie1 = new Agent{0, -1, allies};
  Agent *allie2 = new Agent{-1, 0, allies};
  Agent *allie3 = new Agent{1, 0, allies};

  Agent *ennemi1 = new Agent{1, -1, ennemis};
  Agent *ennemi2 = new Agent{-1, 1, ennemis};
  Agent *ennemi3 = new Agent{0, 1, ennemis};

  // Voisinage vide
  Agent *voisinage[6];
  for (int i = 0; i < 6; ++i)
  {
    voisinage[i] = nullptr;
  }

  SECTION("Un copain autour")
  {
    voisinage[2] = allie1;

    agentCentral.partagerMemoireAuVoisinage(voisinage);

    // Vérification de l'apprentissage -> Même niveau donc change pas
    REQUIRE((*allie1).getMemoire().getDivision() == Approx(0.3333).epsilon(eps));
    REQUIRE((*allie1).getMemoire().getDeplacement() == Approx(0.333).epsilon(eps));
    REQUIRE((*allie1).getMemoire().getRenforcement() == Approx(0.333).epsilon(eps));
  }
}

TEST_CASE("Affichage carte")
{
	Carte carte{};

	//test de creation de la carte
  carte.afficherCarte();
  cout << "-----" << endl;

	//test de coloration des cases
  carte.changerCase(3, 6, EQUIPE::ROUGE);
  carte.changerCase(7, 7, EQUIPE::ROUGE);
  for (int i  = 3; i < 7; i++)
  {
      for (int j = 2; j < 5; j++)
      {
          carte.changerCase(i, j, EQUIPE::BLEU);
      }
  }
	carte.afficherCarte();
	cout << "-----" << endl;

	//test d'ajout et d'affichage d'un agent
  Agent * agent1 = new Agent(5, 5, EQUIPE::ROUGE);
  carte.setAgent(agent1->getX(), agent1->getY(), agent1);
  carte.changerCase(agent1->getX(), agent1->getY(), agent1->getMemoire().getEquipe());
  carte.afficherCarte();
  cout << "-----" << endl;

  //test d'affichage du voisinage en terme de couleur de cases
  EQUIPE voisinage[6];
  carte.casesAdjacentes(agent1, voisinage);
  REQUIRE(voisinage[0] == EQUIPE::NEUTRE);
  REQUIRE(voisinage[1] == EQUIPE::BLEU);
  REQUIRE(voisinage[2] == EQUIPE::BLEU);
  REQUIRE(voisinage[3] == EQUIPE::NEUTRE);
  REQUIRE(voisinage[4] == EQUIPE::NEUTRE);
  REQUIRE(voisinage[5] == EQUIPE::NEUTRE);


	//test de deplacement unitaire de l'agent
	Point origine{5,5};
	Point dest{4,5};
	carte.deplacerAgent(agent1, origine, dest);
	origine.setX(4);
	dest.setX(3);
	carte.deplacerAgent(agent1, origine, dest);
	origine.setX(3);
	dest.setY(6);
	carte.deplacerAgent(agent1, origine, dest);
	origine.setY(6);
	dest.setY(7);
	carte.deplacerAgent(agent1, origine, dest);
	origine.setY(7);
	dest.setY(8);
	carte.deplacerAgent(agent1, origine, dest);
	origine.setY(8);
	carte.afficherCarte();
	cout << "-----" << endl;
}