#include <stdio.h>
#define TAM 7
#define MOVIMENTOS_MAX 31

int tabuleiro[TAM][TAM] =
{
  {0, 0, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, -1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {0, 0, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 0}
};

// Estrutura para armazenar os movimentos das peças
typedef struct {
  int origem_x, origem_y;
  int destino_x, destino_y;
} Movimento;

Movimento movimentos[MOVIMENTOS_MAX];
int num_movimentos = 0;
Movimento solucoes[MOVIMENTOS_MAX];
int num_solucoes = 0;

// Função para imprimir o estado do tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      if (tabuleiro[i][j] == 1) {
        printf(" O ");
      } else if (tabuleiro[i][j] == -1) {
        printf("   "); // Espaço em branco
      } else {
        printf(" # ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

// Função para verificar se o movimento é válido
int movimentoEhValido(int x1, int y1, int x2, int y2) {
  if (x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM) {
    return 0;
  }
  if (tabuleiro[x1][y1] != 1 || tabuleiro[x2][y2] != -1) {
    return 0;
  }
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;
  if (xMedia < 0 || xMedia >= TAM || yMedia < 0 || yMedia >= TAM) {
    return 0;
  }
  if (tabuleiro[xMedia][yMedia] != 1) {
    return 0;
  }
  return 1;
}

// Função para movimentar a peça
void movimentarPeca(int x1, int y1, int x2, int y2) {
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;
  tabuleiro[x1][y1] = -1;
  tabuleiro[xMedia][yMedia] = -1;
  tabuleiro[x2][y2] = 1;
  // Armazena o movimento
  movimentos[num_movimentos++] = (Movimento){x1, y1, x2, y2};
}

// Função para desfazer o último movimento
void desfazerMovimento(int x1, int y1, int x2, int y2) {
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;
  tabuleiro[x1][y1] = 1;
  tabuleiro[xMedia][yMedia] = 1;
  tabuleiro[x2][y2] = -1;
  // Desfaz o último movimento armazenado
  num_movimentos--;
}

// Função para resolver o tabuleiro
int resolverTabuleiro(int movimentosRestantes) {
  if (movimentosRestantes == 0 && tabuleiro[3][3] == 1) {
    // Armazena a solução encontrada
    num_solucoes = num_movimentos;
    for (int i = 0; i < num_solucoes; i++) {
      solucoes[i] = movimentos[i];
    }
    return 1;
  }
  int direcaoX[] = {2, -2, 0, 0};
  int direcaoY[] = {0, 0, 2, -2};
  for (int x1 = 0; x1 < TAM; x1++) {
    for (int y1 = 0; y1 < TAM; y1++) {
      if (tabuleiro[x1][y1] == 1) {
        for (int i = 0; i < 4; i++) {
          int x2 = x1 + direcaoX[i];
          int y2 = y1 + direcaoY[i];
          if (movimentoEhValido(x1, y1, x2, y2)) {
            movimentarPeca(x1, y1, x2, y2);
            if (resolverTabuleiro(movimentosRestantes - 1)) {
              return 1;
            }
            desfazerMovimento(x1, y1, x2, y2);
          }
        }
      }
    }
  }
  return 0;
}

// Função para imprimir a sequência de movimentos
void imprimirCaminho() {
  printf("Sequência de movimentos:\n");
  for (int i = 0; i < num_solucoes; i++) {
    printf("Movimento %d: (%d, %d) -> (%d, %d)\n",
           i + 1,
           solucoes[i].origem_x, solucoes[i].origem_y,
           solucoes[i].destino_x, solucoes[i].destino_y);
  }
}

// Função para salvar os movimentos em um arquivo
void salvarMovimentosEmArquivo(const char* nomeArquivo) {
  FILE* arquivo = fopen(nomeArquivo, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  fprintf(arquivo, "Sequência de movimentos:\n");
  for (int i = 0; i < num_solucoes; i++) {
    fprintf(arquivo, "Movimento %d: (%d, %d) -> (%d, %d)\n",
            i + 1,
            solucoes[i].origem_x, solucoes[i].origem_y,
            solucoes[i].destino_x, solucoes[i].destino_y);
  }
  fclose(arquivo);
  printf("Movimentos salvos no arquivo %s\n", nomeArquivo);
}

// Função principal
int main(void) {
  printf("Estado inicial do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);
  if (resolverTabuleiro(MOVIMENTOS_MAX)) {
    printf("Solução encontrada!\n");
    imprimirCaminho();
    
    // Imprime o estado do tabuleiro após cada movimento da solução
    for (int i = 0; i < num_solucoes; i++) {
      int x1 = solucoes[i].origem_x;
      int y1 = solucoes[i].origem_y;
      int x2 = solucoes[i].destino_x;
      int y2 = solucoes[i].destino_y;
      
      // Aplica o movimento
      movimentarPeca(x1, y1, x2, y2);
      
      // Imprime o estado atual do tabuleiro
      printf("Estado do tabuleiro após o movimento %d:\n", i + 1);
      imprimirTabuleiro(tabuleiro);
      
      // Desfaz o movimento para o próximo movimento
      desfazerMovimento(x1, y1, x2, y2);
    }
    
    salvarMovimentosEmArquivo("movimentos_resta_um.txt");
  } else {
    printf("Não foi possível encontrar uma solução.\n");
  }
  printf("Estado final do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);
  return 0;
}
