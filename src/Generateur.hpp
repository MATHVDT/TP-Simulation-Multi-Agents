/**
 * @file Generateur.hpp
 * @brief 
 */
#ifndef GENERATEUR_HPP
#define GENERATEUR_HPP

#include "mersennetwister.hpp"
#include <cstdio>
#include <exception>

class Generateur
{
public:
    static MtRng32 rand32;
    static MtRng64 rand64;

public:
    Generateur();

    static void initGen();

    static void test64();
    static void test32();
    static void mersenneTest();

    static double rand0_1() { return rand32.getReal2(); }
    static int randEntier() { return rand32.getInt(); }
    static int randUniform(int a, int b) { return a + (b - a) * rand32.getInt(); }
};

#endif
