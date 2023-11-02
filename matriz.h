// cabeçalhos e structs

#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
struct Celula *direita, *abaixo;
int linha, coluna;
float valor;
} Celula;

typedef struct {
Celula *cabeca;
int nlin, ncol;
} Matriz;