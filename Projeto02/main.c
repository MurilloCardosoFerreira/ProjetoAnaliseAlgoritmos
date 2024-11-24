//Nome: Alexandre Luppi Severo e Silva   RA: 10419724
//Nome: DAVI DE CARVALHO SAMPAIO         RA: 10428169
//Nome: MURILLO CARDOSO FERREIRA         RA: 10418082
//Nome: RODRIGO LUCAS ROSALES            RA: 10365071

//Link do Video: https://www.youtube.com/watch?v=aY82SlRZ918&ab_channel=AlexandreLuppi

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Função para iniciar a matriz
void iniciarMatriz(int m[MAX_VERTICES][MAX_VERTICES], int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            m[i][j] = (i == j) ? 0 : INF; 
        }
    }
}

// Função da leitura do Arquivo
int lerArquivo(const char *nomeArquivo, int matriz[MAX_VERTICES][MAX_VERTICES], int *v, int *esquinaIncendio) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    // Caso o arquivo "entrada.txt" não exista na pasta
    if (arquivo == NULL) {
        printf("Não foi possível ler o arquivo...\n");
        return 1;
    }

    // Lê a primeira linha como a esquina onde o incêndio está acontecendo
    fscanf(arquivo, "%d", esquinaIncendio);

    // Lê a segunda linha como o numero de esquinas, e já leva essa informação para criar a matrix
    fscanf(arquivo, "%d", v); 
    iniciarMatriz(matriz, *v);

    // Leitura das triplas no formato (origem, destino e tempo respectivamente)
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

// Função para calcular menor caminho até o incêndio (também conhecido como algoritmo de Dijkstra)
void calcularCaminhoMinimo(int grafo[MAX_VERTICES][MAX_VERTICES], int V, int origem, int dist[], int antecessor[]) {
    // Inicializa um vetor para marcar os vértices já visitados
    int visitado[MAX_VERTICES] = {0};

    // Inicializa as distâncias para todos os vértices com infinito e os antecessores com -1 (indicando que nenhum caminho foi encontrado ainda)
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        antecessor[i] = -1;
    }

    // A distância da origem para ela mesma é zero
    dist[origem] = 0;

    // Itera V-1 vezes para encontrar o caminho mínimo para todos os vértices
    for (int i = 0; i < V - 1; i++) {
        // Encontra o vértice não visitado com a menor distância
        int minDist = INF, minIndex;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // Marca o vértice encontrado como visitado
        visitado[minIndex] = 1;

        // Atualiza as distâncias dos vizinhos se um caminho mais curto for encontrado
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[minIndex][v] != INF && 
                dist[minIndex] + grafo[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + grafo[minIndex][v];
                antecessor[v] = minIndex;
            }
        }
    }
}

// função para imprimir a rota na tela
void imprimirRota(int dist[], int antecessor[], int destino) {
    
    // Se a distância for infinito, não existe caminho até a esquina com o incêndio
    if (dist[destino] == INF) {
        printf("Não há caminho até a esquina %d.\n", destino + 1);
        return;
    }

    // Cria um vetor para armazenar a rota encontrada
    int caminho[MAX_VERTICES];
    
    // Contador para o tamanho da rota
    int count = 0;
    
    // Variável auxiliar para percorrer a rota de trás para frente
    int atual = destino;
    
    while (atual != -1) {
        caminho[count++] = atual;
        atual = antecessor[atual];
    }

    // Imprime a rota encontrada
    printf("Rota até a esquina #%d: ", destino + 1);

    // Imprime os vértices da rota na ordem correta (do destino para a origem)
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", caminho[i] + 1);
    }
    // Imprime o tempo total da rota
    printf("\nTempo calculado para rota = %d min.\n", dist[destino]);
}

// Função para criar e escrever o arquivo de saida
void escreverSaidaEmArquivo(const char *nomeArquivo, int dist[], int antecessor[], int destino) {
    // Abre o arquivo "saida.txt" no modo de escrita, criando-o se não existir
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    // Se a distância for infinito, não existe caminho
    if (dist[destino] == INF) {
        fprintf(arquivo, "Não há caminho até a esquina %d.\n", destino + 1);
    } else {
        // Imprime a rota da esquina com o incêndio
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
        // Escreve no arquivo o tempo total até a esquina
        fprintf(arquivo, "\nTempo calculado para rota = %d min.\n", dist[destino]);
    }

    fclose(arquivo);
}

// Função main
int main() {
    int matriz[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacência do grafo
    int v; // Número de vértices (ou esquinas)
    int esquinaIncendio; // Número da esquina onde ocorreu o incêndio

    // Leitura do arquivo e criação da matrix
    if (lerArquivo("entrada.txt", matriz, &v, &esquinaIncendio) == 0) {

        // imprime as informações lidas no arquivo de entrada
        printf("Arquivo lido com sucesso.\n");
        printf("Esquina do incêndio: %d\n", esquinaIncendio);
        printf("Número de esquinas: %d\n", v);

        //vetores para armazenar as distâncias e os antecessores
        int dist[MAX_VERTICES];
        int antecessor[MAX_VERTICES];
        
        int esquinaInicial = 0;

        // Calcula o caminho mínimo a partir do vértice inicial até todos os outros
        calcularCaminhoMinimo(matriz, v, esquinaInicial, dist, antecessor);

        // Imprime a rota encontrada para a esquina do incêndio
        printf("\nResultado do caminho mínimo:\n");
        imprimirRota(dist, antecessor, esquinaIncendio - 1);

        
        escreverSaidaEmArquivo("saida.txt", dist, antecessor, esquinaIncendio - 1);

    } else {
        printf("Erro ao ler o arquivo.\n"); //mensagem de erro caso não consiga ler o arquivo
    }
    
    return 0;
}
