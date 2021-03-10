#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef DADO_CPP
#define DADO_CPP

using namespace std;

class Dado {
    friend class BMais;
    friend class sequenceset;
    friend class Testing;

public:
    unsigned posicao;
    char *modelo; // elemento chave
    char *cache;
    unsigned tdp;
    char *frequencia;
    char *nucleos;
    float cinebenchR15Single;
    float cinebenchR15Multi;
    float cinebenchR20;

    Dado() {
        modelo = new char[30];
        cache = new char[15];
        frequencia = new char[12];
        nucleos = new char[6];
    }
};

typedef Dado dado;
#endif