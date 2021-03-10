/* Noh - Classe Fundamental
 *
 * Março de 2021 - Estrutura de Dados (GCC216)
 * Copyright 2021 by Gustavo Ribeiro, Pedro Montuani e Vinicius Gomes,
 *
 * Este é o arquivo de implementacao da classe Noh. Essa clase é usada pela
 * Classe BMais, compondo a estrutura da raiz e dos demais nós dessa árvore.
 * Aqui estão presentes o contrutor e o destrutor para cada nó.
 */

#include "Dado.cpp"
#include "configuracao.cpp"
#include <iostream>

class Noh {
    friend class BMais;

private:
    bool folha;
    int quantidade;
    dado itens[CAP_PACOTE];
    Noh *filhos[NUM_FILHOS];
    Noh *pai;

public:
    Noh();
    ~Noh();
};

// inicialização do nó e de seus filhos como NULL
Noh::Noh() {
    quantidade = 0;
    folha = false;
    for (unsigned i = 0; i < NUM_FILHOS; i++) {
        filhos[i] = NULL;
    }
}

// destrutor do nó, desaloca da memória todos os filhos dele
Noh::~Noh() {
    for (int i = 0; i < quantidade + 1; i++) {
        delete filhos[i];
    }
}