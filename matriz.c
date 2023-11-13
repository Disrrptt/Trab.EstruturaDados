// implementação de funções

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Função para criar uma nova célula
Celula *criaCelula(int linha, int coluna, float valor)
{
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;
    novaCelula->direita = NULL;
    novaCelula->abaixo = NULL;
    return novaCelula;
}

// Função para imprimir a matriz
void imprimeMatriz(Matriz mat)
{
    for (int i = 1; i <= mat.nlin; i++)
    {
        for (int j = 1; j <= mat.ncol; j++)
        {
            Celula *atual = mat.cabeca[i][j].abaixo;
            if (atual && atual->coluna == j)
            {
                printf("%.1f ", atual->valor);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Função para ler a matriz a partir de um arquivo
Matriz leMatriz(FILE *arquivo)
{
    Matriz mat; // variavel
    mat.nlin = 0;
    mat.ncol = 0;

    int n, m; // Número de linhas e colunas
    fscanf(arquivo, "%d, %d\n", &n, &m);
    mat.nlin = n;
    mat.ncol = m;
    mat.cabeca = (Celula **)malloc((n + 1) * sizeof(Celula *));

    for (int i = 0; i <= n; i++)
    {
        mat.cabeca[i] = (Celula *)malloc((m + 1) * sizeof(Celula));
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            mat.cabeca[i][j].linha = -1;
            mat.cabeca[i][j].coluna = j;
            mat.cabeca[i][j].valor = 0.0;
            mat.cabeca[i][j].direita = &mat.cabeca[i][j];
            mat.cabeca[i][j].abaixo = &mat.cabeca[i][j];
        }
    }

    int linha, coluna;
    float valor;
    while (fscanf(arquivo, "%d, %d, %f\n", &linha, &coluna, &valor) != EOF)
    {
        Celula *novaCelula = criaCelula(linha, coluna, valor);

        // Insere a célula na lista da linha
        novaCelula->direita = mat.cabeca[linha][coluna].direita;
        mat.cabeca[linha][coluna].direita = novaCelula;

        // Insere a célula na lista da coluna
        novaCelula->abaixo = mat.cabeca[linha][coluna].abaixo;
        mat.cabeca[linha][coluna].abaixo = novaCelula;
    }

    return mat;
}

// Função para somar duas matrizes
Matriz somaMatrizes(Matriz A, Matriz B)
{
    if (A.nlin != B.nlin || A.ncol != B.ncol)
    {
        printf("As matrizes não têm as mesmas dimensões. A soma não é possível.\\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    inicializaMatriz(&C, A.nlin, A.ncol);

    Celula *linhaA = A.cabeca->abaixo;
    Celula *linhaB = B.cabeca->abaixo;

    while (linhaA != A.cabeca && linhaB != B.cabeca)
    {
        Celula *celulaA = linhaA->direita;
        Celula *celulaB = linhaB->direita;

        while (celulaA != linhaA && celulaB != linhaB)
        {
            if (celulaA->coluna < celulaB->coluna)
            {
                insere(&C, celulaA->linha, celulaA->coluna, celulaA->valor);
                celulaA = celulaA->direita;
            }
            else if (celulaA->coluna > celulaB->coluna)
            {
                insere(&C, celulaB->linha, celulaB->coluna, celulaB->valor);
                celulaB = celulaB->direita;
            }
            else
            {
                float soma = celulaA->valor + celulaB->valor;
                if (soma != 0)
                {
                    insere(&C, celulaA->linha, celulaA->coluna, soma);
                }
                celulaA = celulaA->direita;
                celulaB = celulaB->direita;
            }
        }

        while (celulaA != linhaA)
        {
            insere(&C, celulaA->linha, celulaA->coluna, celulaA->valor);
            celulaA = celulaA->direita;
        }

        while (celulaB != linhaB)
        {
            insere(&C, celulaB->linha, celulaB->coluna, celulaB->valor);
            celulaB = celulaB->direita;
        }

        linhaA = linhaA->abaixo;
        linhaB = linhaB->abaixo;
    }

    while (linhaA != A.cabeca)
    {
        Celula *celulaA = linhaA->direita;
        while (celulaA != linhaA)
        {
            insere(&C, celulaA->linha, celulaA->coluna, celulaA->valor);
            celulaA = celulaA->direita;
        }
        linhaA = linhaA->abaixo;
    }

    while (linhaB != B.cabeca)
    {
        Celula *celulaB = linhaB->direita;
        while (celulaB != linhaB)
        {
            insere(&C, celulaB->linha, celulaB->coluna, celulaB->valor);
            celulaB = celulaB->direita;
        }
        linhaB = linhaB->abaixo;
    }

    return C;
}

// Função para multiplicar duas matrizes
Matriz multiplicaMatrizes(Matriz A, Matriz B)
{
    if (A.ncol != B.nlin)
    {
        printf("O número de colunas da matriz A deve ser igual ao número de linhas da matriz B para multiplicação.\\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    inicializaMatriz(&C, A.nlin, B.ncol);

    Celula *linhaA = A.cabeca->abaixo;
    while (linhaA != A.cabeca)
    {
        Celula *celulaA = linhaA->direita;

        Celula *colunaB = B.cabeca->direita;
        while (colunaB != B.cabeca)
        {
            Celula *celulaB = colunaB->abaixo;
            float soma = 0.0;

            while (celulaA != linhaA && celulaB != colunaB)
            {
                if (celulaA->coluna == celulaB->linha)
                {
                    soma += celulaA->valor * celulaB->valor;
                    celulaA = celulaA->direita;
                    celulaB = celulaB->abaixo;
                }
                else if (celulaA->coluna < celulaB->linha)
                {
                    celulaA = celulaA->direita;
                }
                else
                {
                    celulaB = celulaB->abaixo;
                }
            }

            if (soma != 0.0)
            {
                insere(&C, linhaA->abaixo->linha, colunaB->direita->coluna, soma);
            }

            colunaB = colunaB->direita;
        }

        linhaA = linhaA->abaixo;
    }

    return C;
}