#include <stdio.h>

#define N 7

// Tabuleiro inicial do jogo (0 sendo posição inválida)
int tabuleiro[N][N] = {
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, -1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0}
};

// Função para imprimir o estado do tabuleiro
void imprimirTabuleiro(int tabuleiro[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (tabuleiro[i][j] == 0) {
        printf(" 0 ");
      } else {
        printf(" %d ", tabuleiro[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main(void) {
  printf("Estado inicial do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);
  
  return 0;
}
