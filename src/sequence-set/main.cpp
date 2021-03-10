#include "sequenceset.hpp"
#include <iostream>

using namespace std;

int main() {
  sequenceset meuSeqSet("sequenceSetArq.dat");
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
        meuSeqSet.inserirDado(umDado);
        break;
      case 'b': // buscar
        cin >> umaChave;
        umDado = meuSeqSet.buscar(umaChave);
        cout << "Busca: " << umDado.modelo << "/" << umDado.posicao << endl;
        break;
      case 'p': // mostrar estrutura
        meuSeqSet.imprimir();
        break;
      case 'd': // mostrar estrutura
        meuSeqSet.depurar();
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

  return 0;
}
