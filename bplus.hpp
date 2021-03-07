/*
  Projeto de Estrutura de Dados - Implementação de uma árvore B+
    (Estrutura de Dados)
  Sequence Set junto de uma árvore B+ com índices
    para o endereçamento dos pacotes
  Copyright 2021 by Gustavo Ribeiro, Pedro Montuani e Vinicius Gomes

  ****** FUNÇÂO DO CÓDIGO AQUI ******
*/

#include "sequenceset.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class Noh {
  friend class BMais;

private:
  bool folha;
  tipoChave *dados;
  int quantidade;
  Noh **filhos;
  int posFilhosArq[NUM_FILHOS];

public:
  Noh();
};

Noh::Noh() {
  folha = true;
  dados = new tipoChave[CAP_PACOTE];
  filhos = new Noh *[NUM_FILHOS];
}

class BMais {
private:
  Noh *raiz;
  sequenceset *sequenceSet;
  string nomeArqSS;
  string nomeArqIndices;

  void inserirInterno(tipoChave chave, Noh *umNoh, Noh *filho);
  Noh *encontrarPai(Noh *umNoh, Noh *filho);
  void imprimirAux(Noh *raiz, int nivel);
  void lerFilhosArq();

public:
  BMais(string nomeArq);
  void inserir(dado umDado);
  void buscar(tipoChave chave);
  void imprimir();
  void depurar();
};

BMais::BMais(string nomeArq) {
  nomeArqSS = nomeArq + ".txt";
  nomeArqIndices = nomeArq + "Indices.txt";

  sequenceSet = new sequenceset(nomeArqSS);

  raiz = NULL;

  fstream arq(nomeArqIndices.c_str(), ios::in | ios::out | ios::binary);

  if (!arq) {
    ofstream arq(nomeArqIndices.c_str());
  }
  // } else {
  //   raiz = new Noh();

  //   // Ler B+ do arquivo?
  //   arq.read((char *)&(raiz->folha), sizeof(bool));
  //   arq.read((char *)&(raiz->quantidade), sizeof(int));
  //   arq.read((char *)(raiz->dados), sizeof(int) * CAP_PACOTE);
  //   arq.read((char *)(raiz->filhos), sizeof(Noh) * (NUM_FILHOS));
  // }

  arq.close();

  if (raiz != NULL)
    lerFilhosArq();
}

void BMais::lerFilhosArq() {}

void BMais::inserir(dado umDado) {
  tipoChave chave;
  strcpy(chave, umDado.modelo);

  if (raiz == NULL) {
    raiz = new Noh();
    strcpy(raiz->dados[0], chave);
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
          if (strcmp(chave, aux->dados[i]) < 0) {
            aux = aux->filhos[i];
            lugarCerto++;
          }
        }
      }

      if (lugarCerto == 0) {
        aux = aux->filhos[aux->quantidade];
      }
    }

    if (aux->quantidade < int(CAP_PACOTE)) {
      int i = 0;
      while (strcmp(chave, aux->dados[i]) > 0 && i < aux->quantidade) {
        i++;
      }

      for (int j = aux->quantidade; j > i; j--) {
        strcpy(aux->dados[j], aux->dados[j - 1]);
      }

      strcpy(aux->dados[i], chave);
      aux->quantidade++;

      aux->filhos[aux->quantidade] = aux->filhos[aux->quantidade - 1];
      aux->filhos[aux->quantidade - 1] = NULL;
    } else {
      Noh *novaFolha = new Noh();

      tipoChave nohTemp[NUM_FILHOS];

      for (int i = 0; i < int(CAP_PACOTE); i++) {
        strcpy(nohTemp[i], aux->dados[i]);
      }

      int i = 0, j;

      while (strcmp(chave, nohTemp[i]) > 0 && i < int(CAP_PACOTE)) {
        i++;
      }

      for (int j = NUM_FILHOS; j > i; j--) {
        strcpy(nohTemp[j], nohTemp[j - 1]);
      }

      strcpy(nohTemp[i], chave);
      novaFolha->folha = true;

      aux->quantidade = (NUM_FILHOS) / 2;
      novaFolha->quantidade = NUM_FILHOS - (NUM_FILHOS) / 2;

      aux->filhos[aux->quantidade] = novaFolha;

      novaFolha->filhos[novaFolha->quantidade] = aux->filhos[CAP_PACOTE];

      aux->filhos[CAP_PACOTE] = NULL;

      for (i = 0; i < aux->quantidade; i++) {
        strcpy(aux->dados[i], nohTemp[i]);
      }

      for (i = 0, j = aux->quantidade; i < novaFolha->quantidade; i++, j++) {
        strcpy(novaFolha->dados[i], nohTemp[j]);
      }

      if (aux == raiz) {

        Noh *novaRaiz = new Noh();

        strcpy(novaRaiz->dados[0], novaFolha->dados[0]);
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

void BMais::inserirInterno(tipoChave chave, Noh *umNoh, Noh *filho) {
  if (umNoh->quantidade < int(CAP_PACOTE)) {
    int i = 0;

    while (strcmp(chave, umNoh->dados[i]) > 0 && i < umNoh->quantidade) {
      i++;
    }

    for (int j = umNoh->quantidade; j > i; j--) {
      strcpy(umNoh->dados[j], umNoh->dados[j - 1]);
    }

    for (int j = umNoh->quantidade + 1; j > i + 1; j--) {
      umNoh->filhos[j] = umNoh->filhos[j - 1];
    }

    strcpy(umNoh->dados[i], chave);
    umNoh->quantidade++;
    umNoh->filhos[i + 1] = filho;
  } else {
    Noh *novoInterno = new Noh;
    tipoChave dadosTemp[NUM_FILHOS];
    Noh *filhosTemp[NUM_FILHOS + 1];

    for (int i = 0; i < int(CAP_PACOTE); i++) {
      strcpy(dadosTemp[i], umNoh->dados[i]);
    }

    for (int i = 0; i < int(NUM_FILHOS); i++) {
      filhosTemp[i] = umNoh->filhos[i];
    }

    int i = 0, j;

    while (strcmp(chave, dadosTemp[i]) > 0 && i < int(CAP_PACOTE)) {
      i++;
    }

    for (int j = NUM_FILHOS; j > i; j--) {
      strcpy(dadosTemp[j], dadosTemp[j - 1]);
    }

    strcpy(dadosTemp[i], chave);

    for (int j = NUM_FILHOS + 1; j > i + 1; j--) {
      strcpy(dadosTemp[j], dadosTemp[j - 1]);
    }

    filhosTemp[i + 1] = filho;
    novoInterno->folha = false;

    umNoh->quantidade = (NUM_FILHOS) / 2;

    novoInterno->quantidade = int(CAP_PACOTE) - (int(NUM_FILHOS)) / 2;

    for (i = 0, j = umNoh->quantidade + 1; i < novoInterno->quantidade;
         i++, j++) {
      strcpy(novoInterno->dados[i], dadosTemp[j]);
    }

    for (i = 0, j = umNoh->quantidade + 1; i < novoInterno->quantidade + 1;
         i++, j++) {
      novoInterno->filhos[i] = filhosTemp[j];
    }

    if (umNoh == raiz) {
      Noh *novaRaiz = new Noh();

      strcpy(novaRaiz->dados[0], umNoh->dados[umNoh->quantidade]);

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

void BMais::buscar(tipoChave chave) {
  if (raiz == NULL) {
    cout << "A árvore está vazia" << endl;
  } else {
    Noh *aux = raiz;

    while (aux->folha == false) {
      int lugarCerto = 0;

      for (int i = 0; i < aux->quantidade; i++) {
        if (lugarCerto == 0) {
          if (strcmp(chave, aux->dados[i]) < 0) {
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
      if (strcmp(aux->dados[i], chave) == 0) {
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

  for (i = 0; i < raiz->quantidade; i++) {
    if (!raiz->folha) {
      imprimirAux(raiz->filhos[i], nivel + 1);
    }

    cout << raiz->dados[i] << '/' << nivel << ' ';
  }

  // if (!raiz->folha) {
  //   cout << "?";
  //   imprimirAux(raiz->filhos[i], nivel + 1);
  // }
}

void BMais::depurar() {}