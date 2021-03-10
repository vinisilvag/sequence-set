#include "../general/configuracao.hpp"
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

Noh::Noh() {
  quantidade = 0;
  folha = false;
  for (int i = 0; i < NUM_FILHOS; i++) {
    filhos[i] = NULL;
  }
}

Noh::~Noh() {
  for (int i = 0; i < quantidade + 1; i++) {
    delete filhos[i];
  }
}