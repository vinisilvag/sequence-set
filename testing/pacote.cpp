/* Vetor Expansível - Pacote de dados
 *
 * by Joukim, Fevereiro de 2021 - Estrutura de Dados (GCC216)
 * Caracteristicas da primeira implementação - fevereiro de 2021:
 * -> tamanho do pacote e tipo de dados definidos
 * -> em arquivo de configuração
 */

#ifndef DADO_CPP
#include "Dado.cpp"
#endif
#ifndef CONFIGURACAO_CPP
#include "configuracao.cpp"
#endif
#ifndef IOSTREAM
#include <iostream>
#endif
#ifndef STRING_H
#include <string.h>
#endif

using namespace std;

// essa classe também poderia se chamar bloco, pagina, packet ou pedaco
class pacote {
    friend class sequenceset;
    friend class bmais;
    // classe não possui métodos públicos
    // objetos da classe são criados e manuseados
    // apenas pela classe sequenceset
private:
    dado elementos[CAP_PACOTE];
    unsigned numElementos;
    int posProximoPacote;
    pacote() : numElementos(0), posProximoPacote(POS_INVALIDA) {}
    bool cheio() { return (numElementos == CAP_PACOTE); }
    void inserir(dado umDado);
    inline bool chaveEhMaiorQueTodos(tipoChave chave);
    inline bool chaveEhMenorQueTodos(tipoChave chave);
    void imprimir();
};

void pacote::inserir(dado umDado) {
    int posicao = numElementos - 1;
    // Faz a procura pela posição de inserção do elemento de forma decrescente
    while ((posicao >= 0) and
           strcmp(umDado.modelo, elementos[posicao].modelo) < 0) {
        elementos[posicao + 1] = elementos[posicao];
        posicao--;
    }
    elementos[posicao + 1] = umDado;
    numElementos++;
}

void pacote::imprimir() {
    cout << "[";
    for (unsigned i = 0; i < numElementos; i++)
        cout << "(Posicao: " << elementos[i].posicao
             << " / Modelo: " << elementos[i].modelo
             << " / Cache: " << elementos[i].cache << "/TDP: " << elementos[i].tdp
             << " / Frequencia: " << elementos[i].frequencia
             << " / Nucleos: " << elementos[i].nucleos
             << " / Cinebench's: " << elementos[i].cinebenchR15Single << ", "
             << elementos[i].cinebenchR15Multi << " e " << elementos[i].cinebenchR20
             << ")" << endl;
    cout << "]";
}

bool pacote::chaveEhMaiorQueTodos(tipoChave chave) {
    return (strcmp(elementos[numElementos - 1].modelo, chave) < 0);
}

bool pacote::chaveEhMenorQueTodos(tipoChave chave) {
    return (strcmp(elementos[0].modelo, chave) > 0);
}
