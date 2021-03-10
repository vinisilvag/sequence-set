#include "bplus.cpp"
#include "sequenceset.cpp"
#include <algorithm>
#include <chrono>

#include <cstdlib>
#include <ctime>

#include "Report.cpp"

using namespace std;
using namespace std::chrono;

class Testing {
public:
    Testing(int tamanhoLista, int intervaloRandom, Report *bMaisReport, Report *sequenceSetReport) {
        srand((unsigned)time(0));

        cout << "Iniciando conjunto de testes em árvores binárias" << endl
             << endl
             << "Número de inserções e buscas: " << tamanhoLista << endl
             << endl;

        this->minhaBMais = new BMais();
        sequenceset meuSeqSet("sequenceSetArq.dat");
        this->meuSeqSet = &meuSeqSet;

        this->intervaloRandom = intervaloRandom;

        this->tamanhoListas = tamanhoLista;
        this->inputs = new dado[tamanhoListas];
        this->buscasComResultado = new dado[tamanhoListas];
        this->buscasSemResultado = new dado[tamanhoListas];

        this->bMaisReport = bMaisReport;
        this->sequenceSetReport = sequenceSetReport;

        this->createInputsList();
        this->createSearchListWithResult();
        this->createSearchListWithoutResult();
    }

    void testBmais(int numTeste) {
        int numeroAcessos;

        cout << "Iniciando testes na árvore B+" << endl
             << endl
             << "Inserindo valores" << endl;

        this->startCounting();
        this->bMaisInsertions();
        this->stopCounting();
        cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
             << endl;
        this->bMaisReport->inserir(numTeste, this->tamanhoListas, "Inserção", this->getExecutionTime());

        cout << "Iniciando buscas com resultado" << endl;
        this->startCounting();
        this->bMaisSearchesWithResults();
        this->stopCounting();
        cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
             << endl;
        this->bMaisReport->inserir(numTeste, this->tamanhoListas, "Busca Resultados", this->getExecutionTime());

        // cout << "Iniciando buscas sem resultado" << endl;
        // this->startCounting();
        // this->bMaisSearchesWithoutResults();
        // this->stopCounting();
        // cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
        //      << endl
        //      << endl;
        // this->bMaisReport->inserir(numTeste, this->tamanhoListas, "Busca S Resultados", this->getExecutionTime());
    }

    void testSequenceSet(int numTeste) {
        int numeroAcessos;

        cout << "Iniciando testes na SequenceSet" << endl
             << endl
             << "Inserindo valores" << endl;

        this->startCounting();
        this->sequenceSetInsertions();
        this->stopCounting();
        cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
             << endl;
        this->sequenceSetReport->inserir(numTeste, this->tamanhoListas, "Inserção", this->getExecutionTime());

        cout << "Iniciando buscas com resultado" << endl;
        this->startCounting();
        this->sequenceSetSearchesWithResults();
        this->stopCounting();
        cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
             << endl;
        this->sequenceSetReport->inserir(numTeste, this->tamanhoListas, "Busca Resultados", this->getExecutionTime());

        // cout << "Iniciando buscas sem resultado" << endl;
        // this->startCounting();
        // this->seuqenceSetSearchesWithoutResults();
        // this->stopCounting();
        // cout << "Duração: " << this->getExecutionTime() << " microssegundos" << endl
        //      << endl
        //      << endl;
        // this->sequenceSetReport->inserir(numTeste, this->tamanhoListas, "Busca S Resultados", this->getExecutionTime());
    }

private:
    int tamanhoListas;
    int intervaloRandom;
    BMais *minhaBMais;
    sequenceset *meuSeqSet;
    dado *inputs;
    dado *buscasComResultado;
    dado *buscasSemResultado;
    Report *bMaisReport;
    Report *sequenceSetReport;

    std::chrono::system_clock::time_point timeStart;
    std::chrono::system_clock::time_point timeStop;

    char *palavraAleatoria(int tamanho = 6) {
        char texto[tamanho];

        for (int i = 0; i < tamanho; i++) {
            char letter = 97 + rand() % 26;

            texto[i] = letter;
        }

        return texto;
    }

    void createInputsList() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            unsigned tdp = rand() % 1000;
            float cinebenchSingle = rand() % 120;
            float cinebenchMultiple = rand() % 120;
            float cinebenchR20 = rand() % 120;

            Dado *tempDado = new Dado();
            tempDado->posicao = i;
            tempDado->modelo = this->palavraAleatoria(30);
            tempDado->cache = this->palavraAleatoria(15);
            tempDado->tdp = tdp;
            tempDado->frequencia = this->palavraAleatoria(12);
            tempDado->nucleos = this->palavraAleatoria(6);
            tempDado->cinebenchR15Single = cinebenchSingle;
            tempDado->cinebenchR15Multi = cinebenchMultiple;
            tempDado->cinebenchR20 = cinebenchR20;
        };
    }

    void createSearchListWithResult() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            int posicao = (rand() % this->tamanhoListas);
            this->buscasComResultado[i] = this->inputs[posicao];
        };
    }

    void createSearchListWithoutResult() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            char *value = this->palavraAleatoria(30);
            while (hasValueInList(value, this->inputs, this->tamanhoListas)) {
                value = this->palavraAleatoria(30);
            }
            dado tempDado;
            tempDado.modelo = value;
            this->buscasSemResultado[i] = tempDado;
        };
    }

    void printList(dado list[], int size) {
        for (int i = 0; i < size; i++) {
            cout << list[i].modelo << " ";
        }
    }

    void printAllLists() {
        cout << "Lista de valores inseridos nas árvores: " << endl;
        this->printList(this->inputs, this->tamanhoListas);
        cout << endl
             << endl;
        cout << "Lista de valores buscados presentes nas listas: " << endl;
        this->printList(this->buscasComResultado, this->tamanhoListas);
        cout << endl
             << endl;
        cout << "Lista de valores buscados sem resultado nas listas: " << endl;
        this->printList(this->buscasSemResultado, this->tamanhoListas);

        cout << endl
             << endl;
    }

    bool hasValueInList(char *value, dado list[], int size) {
        for (int i = 0; i < size; i++) {
            if (list[i].modelo == value) {
                return true;
            }
        }
        return false;
    }

    void startCounting() {
        this->timeStart = high_resolution_clock::now();
    }

    void stopCounting() {
        this->timeStop = high_resolution_clock::now();
    }

    int64_t getExecutionTime() {
        return duration_cast<microseconds>(this->timeStop - this->timeStart).count();
    }

    void bMaisInsertions() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->minhaBMais->inserir(this->inputs[i]);
        }
    }

    int bMaisSearchesWithResults() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->minhaBMais->buscar(this->buscasComResultado[i].modelo);
        }
    }

    int bMaisSearchesWithoutResults() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->minhaBMais->buscar(this->buscasSemResultado[i].modelo);
        }
    }

    int sequenceSetInsertions() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->meuSeqSet->inserirDado(this->inputs[i]);
        }
    }

    int sequenceSetSearchesWithResults() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->meuSeqSet->buscar(this->buscasComResultado[i].modelo);
        }
    }

    int seuqenceSetSearchesWithoutResults() {
        for (int i = 0; i < this->tamanhoListas; i++) {
            this->meuSeqSet->buscar(this->buscasSemResultado[i].modelo);
        }
    }
};