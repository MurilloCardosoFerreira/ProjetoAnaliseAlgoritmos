//Nome: Alexandre Luppi Severo e Silva      RA: 10419724
//Nome: Murillo Cardoso Ferreira            RA: 10418082
//Nome: Davi de Carvalho Sampaio            RA: 10428169


#include <stdio.h>
#include <stdlib.h> // Para malloc e free

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

// Estrutura para armazenar o estado do tabuleiro
typedef struct {
  int tabuleiro[TAM][TAM];
} EstadoTabuleiro;

Movimento movimentos[MOVIMENTOS_MAX];
EstadoTabuleiro estados[MOVIMENTOS_MAX];
int num_movimentos = 0;

// Função para copiar o estado do tabuleiro
void copiarTabuleiro(int origem[TAM][TAM], EstadoTabuleiro* destino) {
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      destino->tabuleiro[i][j] = origem[i][j];
    }
  }
}

// Função para imprimir o estado do tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      if (tabuleiro[i][j] == 0) {
        printf(" # ");
      } else if (tabuleiro[i][j] == 1) {
        printf(" O ");
      } else if (tabuleiro[i][j] == -1) {
        printf("   "); // Espaço em branco
      }
    }
    printf("\n");
  }
  printf("\n");
}

// Função para salvar todos os estados do tabuleiro em um arquivo
// Função para salvar todos os estados do tabuleiro em um arquivo
void salvarTodosEstadosEmArquivo(const char* nomeArquivo) {
  FILE* arquivo = fopen(nomeArquivo, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  fprintf(arquivo, "Estados do tabuleiro:\n");
  for (int i = 0; i < num_movimentos; i++) {
    fprintf(arquivo, "Estado %d:\n", i + 1);
    for (int linha = 0; linha < TAM; linha++) {
      for (int coluna = 0; coluna < TAM; coluna++) {
        if (estados[i].tabuleiro[linha][coluna] == 0) {
          fprintf(arquivo, " # ");
        } else if (estados[i].tabuleiro[linha][coluna] == 1) {
          fprintf(arquivo, " O ");
        } else if (estados[i].tabuleiro[linha][coluna] == -1) {
          fprintf(arquivo, "   "); // Espaço em branco
        }
      }
      fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "\n");
  }

  // Imprime o estado final do tabuleiro
  fprintf(arquivo, "Estado final do tabuleiro:\n");
  for (int linha = 0; linha < TAM; linha++) {
    for (int coluna = 0; coluna < TAM; coluna++) {
      if (tabuleiro[linha][coluna] == 0) {
        fprintf(arquivo, " # ");
      } else if (tabuleiro[linha][coluna] == 1) {
        fprintf(arquivo, " O ");
      } else if (tabuleiro[linha][coluna] == -1) {
        fprintf(arquivo, "   "); // Espaço em branco
      }
    }
    fprintf(arquivo, "\n");
  }

  fclose(arquivo);
  printf("Estados salvos no arquivo %s\n", nomeArquivo);
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

  // Armazena o estado atual do tabuleiro antes do movimento
  copiarTabuleiro(tabuleiro, &estados[num_movimentos]);

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

// Função principal
int main(void) 
{
  // Inicializa o estado do tabuleiro no início
  copiarTabuleiro(tabuleiro, &estados[0]);
  num_movimentos = 0;

  printf("Estado inicial do tabuleiro:\n");
  imprimirTabuleiro(tabuleiro);

  if (resolverTabuleiro(MOVIMENTOS_MAX))
  {
    printf("Solução encontrada!\n");

    // Imprime o estado do tabuleiro após cada movimento
    for (int i = 0; i < num_movimentos; i++) {
      printf("Estado do tabuleiro após o movimento %d:\n", i + 1);
      imprimirTabuleiro(estados[i].tabuleiro);
    }

    // Imprime o estado final do tabuleiro
    printf("Estado final do tabuleiro:\n");
    imprimirTabuleiro(tabuleiro);

    // Salva todos os estados do tabuleiro em um arquivo
    salvarTodosEstadosEmArquivo("RestaUm.out");
  }
  else
  {
    printf("Não foi possível encontrar uma solução.\n");
  }

  return 0;
}
