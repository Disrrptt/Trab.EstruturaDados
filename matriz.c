//implementação de funções

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
 

// Função para criar uma nova célula
Celula *criaCelula(int linha, int coluna, float valor) {
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;
    novaCelula->direita = NULL;
    novaCelula->abaixo = NULL;
    return novaCelula;
}

// Função para imprimir a matriz
void imprimeMatriz(Matriz mat) {
    for (int i = 1; i <= mat.nlin; i++) {
        for (int j = 1; j <= mat.ncol; j++) {
            Celula *atual = mat.cabeca[i][j].abaixo;
            if (atual && atual->coluna == j) {
                printf("%.1f ", atual->valor);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Função para ler a matriz a partir de um arquivo
Matriz leMatriz(FILE *arquivo) {
    Matriz mat; //variavel
    mat.nlin = 0;
    mat.ncol = 0;

    int n, m; // Número de linhas e colunas
    fscanf(arquivo, "%d, %d\n", &n, &m);
    mat.nlin = n;
    mat.ncol = m;
    mat.cabeca = (Celula **)malloc((n + 1) * sizeof(Celula *));

    for (int i = 0; i <= n; i++) {
        mat.cabeca[i] = (Celula *)malloc((m + 1) * sizeof(Celula));
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mat.cabeca[i][j].linha = -1;
            mat.cabeca[i][j].coluna = j;
            mat.cabeca[i][j].valor = 0.0;
            mat.cabeca[i][j].direita = &mat.cabeca[i][j];
            mat.cabeca[i][j].abaixo = &mat.cabeca[i][j];
        }
    }

    int linha, coluna;
    float valor;
    while (fscanf(arquivo, "%d, %d, %f\n", &linha, &coluna, &valor) != EOF) {
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