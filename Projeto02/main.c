#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF INT_MAX

void iniciarMatriz(int m[MAX_VERTICES][MAX_VERTICES], int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            m[i][j] = (i == j) ? 0 : INF; 
        }
    }
}

int lerArquivo(const char *nomeArquivo, int matriz[MAX_VERTICES][MAX_VERTICES], int *v, int *esquinaIncendio) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        printf("Não foi possível ler o arquivo...\n");
        return 1;
    }
    
    fscanf(arquivo, "%d", esquinaIncendio);
    fscanf(arquivo, "%d", v); 
    iniciarMatriz(matriz, *v); 
    
    int origem, destino, tempo;

    while (fscanf(arquivo, "%d", &origem) == 1 && origem != 0) {
        fscanf(arquivo, "%d %d", &destino, &tempo);
        
        if (origem > 0 && origem <= *v && destino > 0 && destino <= *v) {
            matriz[origem - 1][destino - 1] = tempo;
        } else {
            printf("Origem ou destino fora do intervalo válido...\n");
        }
    }
    
    fclose(arquivo); 
    return 0; 
}

void calcularCaminhoMinimo(int grafo[MAX_VERTICES][MAX_VERTICES], int V, int origem, int dist[], int antecessor[]) {
    int visitado[MAX_VERTICES] = {0};  
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        antecessor[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 0; i < V - 1; i++) {
        int minDist = INF, minIndex;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }
        visitado[minIndex] = 1;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[minIndex][v] != INF && 
                dist[minIndex] + grafo[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + grafo[minIndex][v];
                antecessor[v] = minIndex;
            }
        }
    }
}

void imprimirRota(int dist[], int antecessor[], int destino) {
    if (dist[destino] == INF) {
        printf("Não há caminho até a esquina %d.\n", destino + 1);
        return;
    }

    int caminho[MAX_VERTICES];
    int count = 0, atual = destino;
    while (atual != -1) {
        caminho[count++] = atual;
        atual = antecessor[atual];
    }

    printf("Rota até a esquina #%d: ", destino + 1);
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", caminho[i] + 1);
    }
    printf("\nTempo calculado para rota = %d min.\n", dist[destino]);
}

void escreverSaidaEmArquivo(const char *nomeArquivo, int dist[], int antecessor[], int destino) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    if (dist[destino] == INF) {
        fprintf(arquivo, "Não há caminho até a esquina %d.\n", destino + 1);
    } else {
        fprintf(arquivo, "Rota até a esquina #%d: ", destino + 1);
        int caminho[MAX_VERTICES];
        int count = 0, atual = destino;
        while (atual != -1) {
            caminho[count++] = atual;
            atual = antecessor[atual];
        }
        for (int i = count - 1; i >= 0; i--) {
            fprintf(arquivo, "%d ", caminho[i] + 1);
        }
        fprintf(arquivo, "\nTempo calculado para rota = %d min.\n", dist[destino]);
    }

    fclose(arquivo);
}

int main() {
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int v;
    int esquinaIncendio;
    
    if (lerArquivo("entrada.txt", matriz, &v, &esquinaIncendio) == 0) {
        printf("Arquivo lido com sucesso.\n");
        printf("Esquina do incêndio: %d\n", esquinaIncendio);
        printf("Número de esquinas: %d\n", v);

        int dist[MAX_VERTICES];
        int antecessor[MAX_VERTICES];
        
        int esquinaInicial = 0;
        
        calcularCaminhoMinimo(matriz, v, esquinaInicial, dist, antecessor);
        
        printf("\nResultado do caminho mínimo:\n");
        imprimirRota(dist, antecessor, esquinaIncendio - 1);
        
        escreverSaidaEmArquivo("saida.txt", dist, antecessor, esquinaIncendio - 1);

    } else {
        printf("Erro ao ler o arquivo.\n");
    }
    
    return 0;
}
