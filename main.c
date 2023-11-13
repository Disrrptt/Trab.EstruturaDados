#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main()
{
    FILE *arquivo = fopen("C:\\Users\\luiza\\Estrutura de dados\\Trab.EstruturaDados\\matriz_esparsa.txt", "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo.");
        return 1;
    }

    Matriz mat = leMatriz(arquivo);

    printf("Matriz A:\n");
    imprimeMatriz(mat);

    fclose(arquivo);

    printf("\nSoma das Matrizes A e B:\n");
    C = somaMatrizes(A, B);
    imprimeMatriz(C);

    printf("\nMultiplicação das Matrizes A e B:\n");
    C = multiplicaMatrizes(A, B);
    imprimeMatriz(C);

    return 0;
}
