#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#include <vector>
#endif

#include <fstream>

using namespace std;

struct Dados {
    int numeroTeste;
    int qtdDados;
    string operacao;
    long int tempoAcesso;
};

class Report {
public:
    Report(string nomeArquivo) {
        this->nomeArquivo = nomeArquivo;
    }

    void inserir(int numeroTeste,
                 int qtdDados,
                 string operacao,
                 long int tempoAcesso) {

        Dados dado = {
            numeroTeste,
            qtdDados,
            operacao,
            tempoAcesso,
        };
        this->testes.push_back(dado);
    }

    void generateCsv() {
        std::ofstream csv;
        csv.open(nomeArquivo);
        csv << "Número do teste;Quantidade de dados;Operação;Tempo de acesso;Número de acessos\n";

        for (int i = 0; i < this->testes.size(); i++) {
            csv << testes[i].numeroTeste;
            csv << ";";
            csv << testes[i].qtdDados;
            csv << ";";
            csv << testes[i].operacao;
            csv << ";";
            csv << testes[i].tempoAcesso;
            csv << "\n";
        }

        csv.close();
    }

private:
    vector<Dados> testes;
    string nomeArquivo;
};