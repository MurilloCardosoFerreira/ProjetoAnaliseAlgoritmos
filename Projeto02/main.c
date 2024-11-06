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
    
    fscanf(arquivo, "%d", esquinaIncendio); 
    fscanf(arquivo, "%d", v);  
    iniciarMatriz(matriz, *v); 
    
    int origem, destino, tempo;
    
    while (fscanf(arquivo, "%d", &origem) == 1 && origem != 0) {
        fscanf(arquivo, "%d %d", &destino, &tempo);
        
        if (origem > 0 && origem <= *v && destino > 0 && destino <= *v) {
            matriz[origem - 1][destino - 1] = tempo; // Atualiza o tempo na matriz
        } else {
            printf("Origem ou destino fora do intervalo válido...\n");
        }
    }
    
    fclose(arquivo);
    return 0;
}

// Função que implementa o algoritmo de Dijkstra
void rotaMaisRapida(int G[MAX_VERTICES][MAX_VERTICES], int n, int origem) {
    int T[n], pred[n];  // T[] armazena os tempos e pred[] as rotas (predecessores)
    int visitado[n];     // Para marcar se o vértice foi visitado ou não

    // Inicializa os vetores
    for (int i = 0; i < n; i++) {
        T[i] = INF;  // Inicializa com distância infinita
        pred[i] = -1; // Não tem predecessor no início
        visitado[i] = 0; // Nenhum vértice foi visitado ainda
    }

    T[origem] = 0;  // A distância da origem para si mesma é 0

    // Algoritmo de Dijkstra
    for (int cont = 0; cont < n; cont++) {
        // Passo 3: Encontra o vértice não visitado com a menor distância
        int minDist = INF, v = -1;
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && T[i] < minDist) {
                minDist = T[i];
                v = i;
            }
        }

        // Se não encontrou vértice, a execução pode ser interrompida
        if (v == -1) break;

        visitado[v] = 1;  // Marca o vértice como visitado

        // Passo 3: Atualiza os vizinhos de v
        for (int i = 0; i < n; i++) {
            if (G[v][i] != INF && !visitado[i]) {
                int novaDist = T[v] + G[v][i];
                if (novaDist < T[i]) {
                    T[i] = novaDist;
                    pred[i] = v;  // Atualiza o predecessor
                }
            }
        }
    }

    // Passo 4: Exibe os resultados (distâncias e caminhos)
    for (int i = 0; i < n; i++) {
        if (i != origem) {
            printf("Rota até a esquina #%d: ", i + 1);
            int caminho[MAX_VERTICES], len = 0;
            int j = i;
            
            // Reconstruindo o caminho
            while (j != origem && j != -1) {
                caminho[len++] = j + 1;  // Converte para 1-indexed
                j = pred[j];
            }
            
            if (j == origem) {
                caminho[len++] = origem + 1;
                
                // Imprime o caminho em ordem
                for (int k = len - 1; k >= 0; k--) {
                    printf("%d ", caminho[k]);
                }
                printf("\n");
                printf("Tempo calculado para rota = %d min.\n", T[i]);
            } else {
                printf("Não existe caminho até essa esquina.\n");
            }
        }
    }
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

        // Chama o algoritmo de rota mais rápida a partir da esquina do incêndio
        rotaMaisRapida(matriz, v, esquinaIncendio - 1); // Lembre-se que os índices começam de 0
    } else {
        printf("Erro ao ler o arquivo.\n");
    }
    
    return 0;
}
