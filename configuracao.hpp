/* Sequence Set - Arquivo de Configuração
 * (tipo de elemento armazenado, tamanho do pacote, etc.)
 *
 * by Joukim, Fevereiro de 2021 - Estrutura de Dados (GCC216)
 * Caracteristicas desta implementação - fevereiro de 2021:
 * -> usa chave/valor como dado de exemplo, mas que pode
 * -> ser trocado com facilidade, usando typedef
 * ->
 * -> tamanho máximo e mínimo do pacote definido por
 * -> constantes (CAP_PACOTE e MIN_PACOTE)
 */

using namespace std;

struct elemento {
  unsigned posicao;
  char modelo[30]; // elemento chave
  char cache[15];
  unsigned tdp;
  char frequencia[12];
  char nucleos[6];
  float cinebenchR15Single;
  float cinebenchR15Multi;
  float cinebenchR20;
};

typedef elemento dado;      // a arvore guarda informacoes do tipo Dado
typedef char tipoChave[30]; // tipo da chave usada na comparação

// capacidade máxima e mínima do pacote
const unsigned CAP_PACOTE = 5;
const unsigned NUM_FILHOS = CAP_PACOTE + 1;
const unsigned MIN_PACOTE = 2;

// posição do elemento do meio do pacote
const unsigned POS_MEIO = 2;

// posição inválida no disco
const int POS_INVALIDA = -1;
