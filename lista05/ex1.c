#include <stdio.h>
#include <string.h>

// imprime todos os numeros binarios em n bits
void imprimeBinario(char binario[], int i, int n)
{
    // verifica se foram posicionados os n bits
    if (i == n)
    {
        binario[i] = '\0';
        printf("%s\n", binario);
        return;
    }

    // caso contrario, faz uma recursão com o bit sendo 0 e depois 1 na posição i
    binario[i] = '0';
    imprimeBinario(binario, i + 1, n);
    
    binario[i] = '1';
    imprimeBinario(binario, i + 1, n);
}

// teste no main
int main()
{
    int n = 3;
    char binario[n + 1];
    
    imprimeBinario(binario, 0, n);
    return 0;
}
