/**
 * @file tests_catch.cpp
 * @brief Fichier contenant les tests unitaires.
 */
#include <fstream>
#include <iostream>

#include "catch.hpp"
#include "Agent.hpp"
#include "Memoire.hpp"

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
  Memoire m1{};
  Memoire m2{};


}