/* Árvore B+ - Classe Principal
 *
 * Março de 2021 - Estrutura de Dados (GCC216)
 * Copyright 2021 by Gustavo Ribeiro, Pedro Montuani e Vinicius Gomes,
 *
 * Este e o arquivo de implementacao da classe BMais, estrutura principal do
 * projeto, que contém um ponteiro para o noh raiz da arvore de indices e os
 * métodos para que a árvore seja devidamente manipulada.
 */

#include "noh.cpp"
#ifndef STRING_H
#include <string.h>
#endif

class BMais {
private:
    Noh *raiz;
    Noh *insereAux(Noh *umNoh, dado umDado, dado &promovido);
    void insereEmNohFolhaNaoCheio(Noh *umNoh, dado umDado);
    Noh *divideNoh(Noh *umNoh, dado &promovido);
    void insereEmNohIntermediarioNaoCheio(Noh *umNoh, Noh *novo, dado &promovido);
    dado buscarAux(Noh *umNoh, tipoChave chave);
    void imprimirAux(Noh *umNoh, int nivel);

public:
    void inserir(dado umDado);
    dado buscar(tipoChave chave);
    void imprimir();
    void depurar();
};

void BMais::inserir(dado umDado) {
    // caso raiz for nula insere na primeira posição dela
    if (raiz == NULL) {
        raiz = new Noh();
        raiz->folha = true;
        raiz->itens[0] = umDado;
        raiz->quantidade = 1;
    } else {
        dado promovido;
        Noh *novo = insereAux(raiz, umDado, promovido);

        if (novo != NULL) {
            Noh *antiga = raiz;
            raiz = new Noh();
            raiz->itens[0] = promovido;
            raiz->quantidade = 1;
            raiz->filhos[0] = antiga;
            raiz->filhos[1] = novo;
        }
    }
}

Noh *BMais::insereAux(Noh *umNoh, dado umDado, dado &promovido) {
    if (umNoh->folha) {
        if (umNoh->quantidade < int(CAP_PACOTE)) {
            insereEmNohFolhaNaoCheio(umNoh, umDado);

            return NULL;
        } else {
            Noh *novo = divideNoh(umNoh, promovido);

            if (strcmp(umDado.modelo, umNoh->itens[POS_MEIO].modelo) <= 0) {
                insereEmNohFolhaNaoCheio(umNoh, umDado);
            } else {
                insereEmNohFolhaNaoCheio(novo, umDado);
            }

            return novo;
        }
    } else {
        int i = umNoh->quantidade - 1;

        while ((i >= 0) && (strcmp(umNoh->itens[i].modelo, umDado.modelo) > 0)) {
            i--;
        }

        Noh *nohAux = insereAux(umNoh->filhos[i + 1], umDado, promovido);

        if (nohAux != NULL) {
            if (umNoh->quantidade < int(CAP_PACOTE)) {
                insereEmNohIntermediarioNaoCheio(umNoh, nohAux, promovido);
                return NULL;
            } else {
                dado provfilho = promovido;
                Noh *novo = divideNoh(umNoh, promovido);

                if (strcmp(umDado.modelo, umNoh->itens[POS_MEIO].modelo) <= 0) {
                    insereEmNohIntermediarioNaoCheio(umNoh, nohAux, provfilho);
                } else {
                    insereEmNohIntermediarioNaoCheio(umNoh, nohAux, provfilho);
                }

                return novo;
            }
        }

        return NULL;
    }
}

void BMais::insereEmNohFolhaNaoCheio(Noh *umNoh, dado umDado) {
    int pos = umNoh->quantidade - 1;

    while (pos >= 0 && strcmp(umNoh->itens[pos].modelo, umDado.modelo) > 0) {
        umNoh->itens[pos + 1] = umNoh->itens[pos];
        pos--;
    }

    umNoh->itens[pos + 1] = umDado;
    umNoh->quantidade++;
}

Noh *BMais::divideNoh(Noh *umNoh, dado &promovido) {
    promovido = umNoh->itens[POS_MEIO];
    Noh *novo = new Noh();
    novo->folha = umNoh->folha;

    novo->itens[0] = umNoh->itens[POS_MEIO];
    novo->itens[1] = umNoh->itens[POS_MEIO + 1];
    novo->itens[2] = umNoh->itens[POS_MEIO + 2];

    novo->quantidade = POS_MEIO + 1;
    umNoh->quantidade = POS_MEIO;

    if (!umNoh->folha) {
        for (unsigned i = 0; i <= POS_MEIO + 1; i++) {
            novo->filhos[i] = umNoh->filhos[POS_MEIO + 0 + i];
        }
    }

    return novo;
}

void BMais::insereEmNohIntermediarioNaoCheio(Noh *umNoh, Noh *novo,
                                             dado &promovido) {
    int pos = umNoh->quantidade - 1;

    while (pos >= 0 && strcmp(umNoh->itens[pos].modelo, promovido.modelo) > 0) {
        umNoh->itens[pos + 1] = umNoh->itens[pos];
        umNoh->filhos[pos + 2] = umNoh->filhos[pos + 1];
        pos--;
    }

    umNoh->itens[pos + 1] = promovido;
    umNoh->filhos[pos + 2] = novo;
    umNoh->quantidade++;
}

dado BMais::buscar(tipoChave chave) {
    if (raiz == NULL) {
        cout << "Árvore vazia" << endl;
    } else {
        dado itemBuscado = buscarAux(raiz, chave);
        return itemBuscado;
    }
}

dado BMais::buscarAux(Noh *umNoh, tipoChave chave) {
    int i = 0;

    while ((i < umNoh->quantidade) &&
           (strcmp(umNoh->itens[i].modelo, chave) <= 0)) {
        i++;
    }

    i--;

    if (strcmp(umNoh->itens[i].modelo, chave) == 0) {
        return umNoh->itens[i];
    } else {
        if (umNoh->folha) {
            Dado emptyDado;
            return emptyDado;
        } else {
            return buscarAux(umNoh->filhos[i + 1], chave);
        }
    }
}

void BMais::imprimir() {
    imprimirAux(raiz, 0);
    cout << endl;
}

void BMais::imprimirAux(Noh *umNoh, int nivel) {
    int i = 0;

    for (i = 0; i < umNoh->quantidade; i++) {
        if (!umNoh->folha) {
            imprimirAux(umNoh->filhos[i], nivel + 1);
        }

        cout << "(Modelo: " << umNoh->itens[i].modelo
             << " / Posicao: " << umNoh->itens[i].posicao << " / Nivel: " << nivel
             << ")" << endl;
    }

    if (!umNoh->folha) {
        imprimirAux(umNoh->filhos[i], nivel + 1);
    }
}

void BMais::depurar() {
    cout << "Esse método não pode ser implementado :(" << endl;
}