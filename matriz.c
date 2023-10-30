//implementação de funções

#include <stdio.h>
#include <stdlib.h>
 

 //função para ler arquivo

void leMatriz(const char *Arquivo,double valor, int *linhas, int *colunas){

FILE *file;
    
    file = fopen("DadosEntradaMatriz.txt", "r");
    //verifica se abre o arquivo e retorna
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

}
