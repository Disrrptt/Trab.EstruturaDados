//testes


int main() {
    FILE *arquivo;
    int m, n;  // Número de linhas e colunas da matriz
    ElementoMatriz *matriz;  // Um vetor de elementos da matriz

    // Abra o arquivo para leitura
    arquivo = fopen("C://Users//luiza.munis//OneDrive//Trab.EstruturaDados//DadosEntradaMatriz.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    // Leia m e n
    fscanf(arquivo, "%d %d", &m, &n);

    // Aloque memória para a matriz
    matriz = (ElementoMatriz *)malloc(sizeof(ElementoMatriz) * m * n);

    if (matriz == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Leia as tuplas (i, j, valor) e preencha a matriz
    for (int k = 0; k < m * n; k++) {
        fscanf(arquivo, "%d %d %lf", &matriz[k].i, &matriz[k].j, &matriz[k].valor);
    }

    // Agora você pode usar a matriz para fazer operações com os elementos não nulos.

    // Feche o arquivo e libere a memória alocada
    fclose(arquivo);
    free(matriz);


    

    return 0;
}