#define MATRIZ

typedef struct Celula
{
    struct Celula *direita, *abaixo;
    int linha, coluna;
    float valor;
} Celula;

typedef struct
{
    Celula **cabeca;
    int nlin, ncol;
} Matriz;

Celula *criaCelula(int linha, int coluna, float valor);
Matriz leMatriz(FILE *arquivo);
void imprimeMatriz(Matriz mat);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
