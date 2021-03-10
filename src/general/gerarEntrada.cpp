/* Gerador de Entrada - Arquivo Auxiliar
 *
 * Março de 2021 - Estrutura de Dados (GCC216)
 * Copyright 2021 by Gustavo Ribeiro, Pedro Montuani e Vinicius Gomes,
 *
 * Este é o arquivo responsável por gerar as entradas randômicas usadas nos
 * códigos da Árvore B+ e do Sequence Set. É um programa simples que gera textos
 * de 6 caracteres e números aleatórios, organiza esses textos e números na
 * forma da entrada do programa e escreve no arquivo.
 */

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  srand((unsigned)time(NULL));

  // cria o arquivo das entradas
  ofstream myfile("entradas.dat");

  // vetor para armazenar as chaves que serão buscadas
  string search[20];

  for (int i = 0; i < 100; i++) {
    string text;

    // iteração que gera os caracteres aleatórios e os insere na string de texto
    for (int i = 0; i < 6; i++) {
      char letter = 97 + rand() % 26;

      text += letter;
    }

    if (i < 20) {
      search[i] = text;
    }

    // número aleatórios sendo gerados
    unsigned tdp = rand() % 1000;

    float cinebench = rand() % 120;

    // escrita no arquivo de todas as inserções que serão realizadas
    myfile << "i " << i + 1 << " " << text << " " << text << " " << tdp << " "
           << text << " " << text << " " << cinebench << " " << cinebench << " "
           << cinebench << endl;
  }

  // escrita no arquivo de todas as buscas que serão feitas
  for (int i = 0; i < 20; i++) {
    myfile << "b " << search[i] << endl;
  }

  // escrita no arquivo da chamada da função de impressão e depuração
  myfile << "p" << endl << "d";

  myfile.close();

  return 0;
}