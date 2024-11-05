#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF INT_MAX

void iniciarMatriz(int m[MAX_VERTICES][MAX_VERTICES], int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            m[i][j] = (i == j) ? 0 : INF; // Inicializa a matriz
        }
    }
}

int lerArquivo(const char *nomeArquivo, int matriz[MAX_VERTICES][MAX_VERTICES], int *v, int *esquinaIncendio) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        printf("Não foi possível ler o arquivo...\n");
        return 1;
    }
    
    fscanf(arquivo, "%d", esquinaIncendio); // Lê a esquina do incêndio
    fscanf(arquivo, "%d", v); // Lê o número de esquinas
    iniciarMatriz(matriz, *v); // Inicializa a matriz de adjacência
    
    int origem, destino, tempo;

    // Corrigido para verificar o valor de origem corretamente
    while (fscanf(arquivo, "%d", &origem) == 1 && origem != 0) {
        fscanf(arquivo, "%d %d", &destino, &tempo);
        
        // Verifica se origem e destino estão dentro do intervalo válido
        if (origem > 0 && origem <= *v && destino > 0 && destino <= *v) {
            matriz[origem - 1][destino - 1] = tempo; // Atualiza o tempo na matriz
        } else {
            printf("Origem ou destino fora do intervalo válido...\n");
        }
    }
    
    fclose(arquivo); // Fechar o arquivo após ler todos os dados
    return 0; // Retorna 0 para indicar sucesso
}

int main() {
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int v;
    int esquinaIncendio;

    if (lerArquivo("entrada.txt", matriz, &v, &esquinaIncendio) == 0) {
        printf("Arquivo lido com sucesso.\n");
        printf("Esquina do incêndio: %d\n", esquinaIncendio);
        printf("Número de esquinas: %d\n", v);
        
        // Para imprimir a matriz de adjacência se necessário
        printf("Matriz de Adjacência:\n");
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (matriz[i][j] == INF) {
                    printf("INF\t");
                } else {
                    printf("%d\t", matriz[i][j]);
                }
            }
            printf("\n");
        }
    } else {
        printf("Erro ao ler o arquivo.\n");
    }
    
    return 0;
}
