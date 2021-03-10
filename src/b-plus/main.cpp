#include "bplus.hpp"
#include <iostream>

using namespace std;

int main() {
  BMais *minhaBMais = new BMais();
  dado umDado;
  tipoChave umaChave;
  char operacao;

  do {
    try {
      cin >> operacao;
      switch (operacao) {
      case 'i': // inserir
        cin >> umDado.posicao;
        cin >> umDado.modelo;
        cin >> umDado.cache;
        cin >> umDado.tdp;
        cin >> umDado.frequencia;
        cin >> umDado.nucleos;
        cin >> umDado.cinebenchR15Single >> umDado.cinebenchR15Multi >>
            umDado.cinebenchR20;
        minhaBMais->inserir(umDado);
        break;
      case 'b': // buscar
        cin >> umaChave;
        umDado = minhaBMais->buscar(umaChave);
        cout << "Elemento encontrado! Modelo: " << umDado.modelo
             << " / Posicao: " << umDado.posicao << endl;
        break;
      case 'p': // mostrar estrutura
        minhaBMais->imprimir();
        break;
      case 'd': // mostrar estrutura
        minhaBMais->depurar();
        break;
      case 's': // sair
        // será tratado no while
        break;
      default:
        cout << "Opção inválida!" << endl;
      }
    } catch (runtime_error &e) {
      cerr << e.what() << endl;
    }
  } while (operacao != 's');

  delete minhaBMais;

  return 0;
}
