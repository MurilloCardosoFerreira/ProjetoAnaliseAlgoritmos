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

  // Armazena o movimento
  movimentos[num_movimentos++] = (Movimento){x1, y1, x2, y2};
}

void desfazerMovimento(int x1, int y1, int x2, int y2)
{
  int xMedia = (x1 + x2) / 2;
  int yMedia = (y1 + y2) / 2;

  tabuleiro[x1][y1] = 1;
  tabuleiro[xMedia][yMedia] = 1;
  tabuleiro[x2][y2] = -1;

  // Desfaz o último movimento armazenado
  num_movimentos--;
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

// Função para imprimir a sequência de movimentos
void imprimirCaminho() {
  printf("Sequência de movimentos:\n");
  for (int i = 0; i < num_movimentos; i++) {
    printf("Movimento %d: (%d, %d) -> (%d, %d)\n",
           i + 1,
           movimentos[i].origem_x, movimentos[i].origem_y,
           movimentos[i].destino_x, movimentos[i].destino_y);
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
  for (int i = 0; i < num_movimentos; i++) {
    fprintf(arquivo, "Movimento %d: (%d, %d) -> (%d, %d)\n",
            i + 1,
            movimentos[i].origem_x, movimentos[i].origem_y,
            movimentos[i].destino_x, movimentos[i].destino_y);
  }

  fclose(arquivo);
  printf("Movimentos salvos no arquivo %s\n", nomeArquivo);
}

// Função principal
int main(void) 
{
  printf("Estado inicial do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);

  if (resolverTabuleiro(MOVIMENTOS_MAX))
  {
    printf("Solução encontrada!\n");
    imprimirCaminho();
    salvarMovimentosEmArquivo("movimentos_resta_um.txt");
  }
  else
  {
    printf("Não foi possível encontrar uma solução.\n");
  }

  printf("Estado final do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);

  return 0;
}
