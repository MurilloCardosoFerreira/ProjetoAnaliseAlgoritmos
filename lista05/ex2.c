#include <stdio.h>
#include <string.h>
// imprime todas as permutações de um placar entre times AxB
void imprimePlacar(char placar[],int i, int n, int m)
{
    // imprime quando todas os gols foram feitos
    if (n == 0 && m == 0)
    {
        placar[i] = '\0';
        printf("%s\n", placar);
        return;
    }

    // se a quantidade de gols ainda não foram todos contabilizados do time A
    if (n > 0)
    {
        placar[i] = 'A';
        imprimePlacar(placar, i + 1, n - 1, m);
    }

    // se a quantidade de gols ainda não foram todos contabilizados do time A
    if (m > 0)
    {
        placar[i] = 'B';
        imprimePlacar(placar, i + 1, n, m - 1);
    }
}

// teste
int main()
{
    int n = 3;
    int m = 1;
    char placar[n + m + 1];
    
    imprimePlacar(placar, 0, n, m);
}
