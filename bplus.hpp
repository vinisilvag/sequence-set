/*
  Projeto de Estrutura de Dados - Implementação de uma árvore B+
    (Estrutura de Dados)
  Sequence Set junto de uma árvore B+ com índices
    para o endereçamento dos pacotes
  Copyright 2021 by Gustavo Ribeiro, Pedro Montuani e Vinicius Gomes

  ****** FUNÇÂO DO CÓDIGO AQUI ******
*/

#include "pacote.hpp"
#include "sequenceset.hpp"
#include <fstream>
#include <iostream>

using namespace std;

const int CAP_MAXIMA = 5;

class Noh {
  friend class BMais;

private:
  bool folha;
  int *dados, quantidade;
  Noh **filhos;

public:
  Noh();
};

Noh::Noh() {
  dados = new int[CAP_PACOTE];
  filhos = new Noh *[NUM_FILHOS];
}

class BMais {
private:
  Noh *raiz;
  sequenceset *sequenceSet;
  string nomeArqSequenceSet;
  string nomeArqIndices;

  void inserirInterno(int item, Noh *umNoh, Noh *filho);
  Noh *encontrarPai(Noh *umNoh, Noh *filho);
  void imprimirAux(Noh *raiz, int nivel);
  void lerFilhosArq();

public:
  BMais(string nomeArq);
  void inserir(int item);
  void buscar(int item);
  void imprimir();
};

BMais::BMais(string nomeArq) {
  nomeArqSequenceSet = nomeArq + ".txt";
  nomeArqIndices = nomeArq + "Indices.txt";

  sequenceSet = new sequenceset(nomeArqSequenceSet);

  fstream arq(nomeArqIndices.c_str(), ios::in | ios::out);

  if (!arq) {
    ofstream arq(nomeArqIndices.c_str());
  } else {
    raiz = new Noh();

    // arq.read((char *)&(raiz->folha), sizeof(bool));
    // arq.read((char *)&(raiz->quantidade), sizeof(int));
    // arq.read((char *)(raiz->dados), sizeof(int) * CAP_PACOTE);
    // arq.read((char *)(raiz->filhos), sizeof(Noh) * (NUM_FILHOS));
  }

  arq.close();

  if (raiz != NULL) {
    lerFilhosArq();
  }

  raiz = NULL;
}

void BMais::inserir(int item) {
  if (raiz == NULL) {
    raiz = new Noh();
    raiz->dados[0] = item;
    raiz->folha = true;
    raiz->quantidade = 1;
  } else {
    Noh *aux = raiz;
    Noh *pai;

    while (aux->folha == false) {
      pai = aux;
      int lugarCerto = 0;

      for (int i = 0; i < aux->quantidade; i++) {
        if (lugarCerto == 0) {
          if (item < aux->dados[i]) {
            aux = aux->filhos[i];
            lugarCerto++;
          }
        }
      }

      if (lugarCerto == 0) {
        aux = aux->filhos[aux->quantidade];
      }
    }

    if (aux->quantidade < CAP_MAXIMA) {
      int i = 0;
      while (item > aux->dados[i] && i < aux->quantidade) {
        i++;
      }

      for (int j = aux->quantidade; j > i; j--) {
        aux->dados[j] = aux->dados[j - 1];
      }

      aux->dados[i] = item;
      aux->quantidade++;

      aux->filhos[aux->quantidade] = aux->filhos[aux->quantidade - 1];
      aux->filhos[aux->quantidade - 1] = NULL;
    } else {
      Noh *novaFolha = new Noh();

      int nohTemp[CAP_MAXIMA + 1];

      for (int i = 0; i < CAP_MAXIMA; i++) {
        nohTemp[i] = aux->dados[i];
      }

      int i = 0, j;

      while (item > nohTemp[i] && i < CAP_MAXIMA) {
        i++;
      }

      for (int j = CAP_MAXIMA + 1; j > i; j--) {
        nohTemp[j] = nohTemp[j - 1];
      }

      nohTemp[i] = item;
      novaFolha->folha = true;

      aux->quantidade = (CAP_MAXIMA + 1) / 2;
      novaFolha->quantidade = CAP_MAXIMA + 1 - (CAP_MAXIMA + 1) / 2;

      aux->filhos[aux->quantidade] = novaFolha;

      novaFolha->filhos[novaFolha->quantidade] = aux->filhos[CAP_MAXIMA];

      aux->filhos[CAP_MAXIMA] = NULL;

      for (i = 0; i < aux->quantidade; i++) {
        aux->dados[i] = nohTemp[i];
      }

      for (i = 0, j = aux->quantidade; i < novaFolha->quantidade; i++, j++) {
        novaFolha->dados[i] = nohTemp[j];
      }

      if (aux == raiz) {

        Noh *novaRaiz = new Noh();

        novaRaiz->dados[0] = novaFolha->dados[0];
        novaRaiz->filhos[0] = aux;
        novaRaiz->filhos[1] = novaFolha;
        novaRaiz->folha = false;
        novaRaiz->quantidade = 1;
        raiz = novaRaiz;
      } else {
        inserirInterno(novaFolha->dados[0], pai, novaFolha);
      }
    }
  }
}

void BMais::inserirInterno(int item, Noh *umNoh, Noh *filho) {
  if (umNoh->quantidade < CAP_PACOTE) {
    int i = 0;

    while (item > umNoh->dados[i] && i < umNoh->quantidade) {
      i++;
    }

    for (int j = umNoh->quantidade; j > i; j--) {

      umNoh->dados[j] = umNoh->dados[j - 1];
    }

    for (int j = umNoh->quantidade + 1; j > i + 1; j--) {
      umNoh->filhos[j] = umNoh->filhos[j - 1];
    }

    umNoh->dados[i] = item;
    umNoh->quantidade++;
    umNoh->filhos[i + 1] = filho;
  } else {
    Noh *novoInterno = new Noh;
    int dadosTemp[NUM_FILHOS];
    Noh *filhosTemp[NUM_FILHOS + 1];

    for (int i = 0; i < CAP_PACOTE; i++) {
      dadosTemp[i] = umNoh->dados[i];
    }

    for (int i = 0; i < NUM_FILHOS; i++) {
      filhosTemp[i] = umNoh->filhos[i];
    }

    int i = 0, j;

    while (item > dadosTemp[i] && i < CAP_PACOTE) {
      i++;
    }

    for (int j = NUM_FILHOS; j > i; j--) {

      dadosTemp[j] = dadosTemp[j - 1];
    }

    dadosTemp[i] = item;

    for (int j = NUM_FILHOS + 1; j > i + 1; j--) {
      dadosTemp[j] = dadosTemp[j - 1];
    }

    filhosTemp[i + 1] = filho;
    novoInterno->folha = false;

    umNoh->quantidade = (NUM_FILHOS) / 2;

    novoInterno->quantidade = CAP_PACOTE - (NUM_FILHOS) / 2;

    for (i = 0, j = umNoh->quantidade + 1; i < novoInterno->quantidade;
         i++, j++) {
      novoInterno->dados[i] = dadosTemp[j];
    }

    for (i = 0, j = umNoh->quantidade + 1; i < novoInterno->quantidade + 1;
         i++, j++) {
      novoInterno->filhos[i] = filhosTemp[j];
    }

    if (umNoh == raiz) {
      Noh *novaRaiz = new Noh();

      novaRaiz->dados[0] = umNoh->dados[umNoh->quantidade];

      novaRaiz->filhos[0] = umNoh;
      novaRaiz->filhos[1] = novoInterno;
      novaRaiz->folha = false;
      novaRaiz->quantidade = 1;
      raiz = novaRaiz;
    } else {
      inserirInterno(umNoh->dados[umNoh->quantidade], encontrarPai(raiz, umNoh),
                     novoInterno);
    }
  }
}

Noh *BMais::encontrarPai(Noh *umNoh, Noh *filho) {
  Noh *pai;

  if (umNoh->folha || (umNoh->filhos[0])->folha) {
    return NULL;
  }

  for (int i = 0; i < umNoh->quantidade + 1; i++) {
    if (umNoh->filhos[i] == filho) {
      pai = umNoh;
      return pai;
    } else {
      pai = encontrarPai(umNoh->filhos[i], filho);

      if (pai != NULL)
        return pai;
    }
  }

  return pai;
}

void BMais::buscar(int item) {
  if (raiz == NULL) {
    cout << "A árvore está vazia" << endl;
  } else {

    Noh *aux = raiz;

    while (aux->folha == false) {
      int lugarCerto = 0;

      for (int i = 0; i < aux->quantidade; i++) {
        if (lugarCerto == 0) {
          if (item < aux->dados[i]) {
            aux = aux->filhos[i];
            lugarCerto++;
          }
        }
      }

      if (lugarCerto == 0) {
        aux = aux->filhos[aux->quantidade];
      }
    }

    for (int i = 0; i < aux->quantidade; i++) {
      if (aux->dados[i] == item) {
        cout << aux->dados[i] << ": Encontrado" << endl;
        return;
      }
    }

    cout << "Elemento não está presente na árvore" << endl;
  }
}

void BMais::imprimir() {
  imprimirAux(raiz, 0);
  cout << endl;
}

void BMais::imprimirAux(Noh *raiz, int nivel) {
  int i;

  for (int i = 0; i < raiz->quantidade; i++) {
    if (!raiz->folha) {
      imprimirAux(raiz->filhos[i], nivel + 1);
    }

    cout << raiz->dados[i] << '/' << nivel << ' ';
  }

  if (!raiz->folha) {
    cout << "?";
    // imprimirAux(raiz->filhos[i], nivel + 1);
  }
}