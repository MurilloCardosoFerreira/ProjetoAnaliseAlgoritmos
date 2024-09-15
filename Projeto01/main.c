#include <stdio.h>

#define TAM 7
#define MOVIMENTOS 31

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

// Função para imprimir o estado do tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
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

int movimentoEhValido(int x1, int y1, int x2, int y2)
{
  if (x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM)
  {
    return 0;
  }
  if (tabuleiro[x1][y1] != 1 || tabuleiro[x2][y2] != -1)
  {
    return 0;
  }

  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;

  if (tabuleiro[xMedia][yMedia] != 1)
  {
    return 0;
  }

  return 1;
}

void movimentarPeca(int x1, int y1, int x2, int y2)
{
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;

  tabuleiro[x1][y1] = -1;
  tabuleiro[xMedia][yMedia] = -1;
  tabuleiro[x2][y2] = 1;
}

void desfazerMovimento(int x1, int y1, int x2, int y2)
{
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;

  tabuleiro[x1][y1] = 1;
  tabuleiro[xMedia][yMedia] = 1;
  tabuleiro[x2][y2] = -1;
}

int resolverTabuleiro(int movimentosRestantes)
{
  if (movimentosRestantes == 0 && tabuleiro[3][3] == 1)
  {
    return 1;
  }

  int direcaoX[] = {2, -2, 0, 0};
  int direcaoY[] = {0, 0, 2, -2};

  for (int x1 = 0; x1 < TAM; x1++)
    for (int y1 = 0; y1 < TAM; y1++)
      {
        if (tabuleiro[x1][y1] == 1)
        {
          for (int i = 0; i < 4; i++)
            {
              int x2 = x1 + direcaoX[i];
              int y2 = y1 + direcaoY[i];

              if (movimentoEhValido(x1, y1, x2, y2))
              {
                movimentarPeca(x1, y1, x2, y2);

                if (resolverTabuleiro(movimentosRestantes - 1))
                {
                  return 1;
                }

                desfazerMovimento(x1, y1, x2, y2);
              }
            }
        }
      }

  return 0;
}

int main(void) 
{
  printf("Estado inicial do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);
  
  if (resolverTabuleiro(MOVIMENTOS))
  {
    printf("Solução encontrada!\n");
  }
  else
  {
    printf("Não foi possível encontrar uma solução.\n");
  }

  printf("Estado final do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);

  return 0;
}
