#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    char tipo[20]; 
} CorpoCeleste;


CorpoCeleste*** criarMapa(int x, int y, int z);
void liberarMapa(CorpoCeleste*** mapa, int x, int y);
void adicionarCorpoCeleste(CorpoCeleste*** mapa, int x, int y, int z, int cx, int cy, int cz, const char* nome, const char* tipo);
void removerCorpoCeleste(CorpoCeleste*** mapa, int cx, int cy, int cz);
void buscarPorCoordenadas(CorpoCeleste*** mapa, int cx, int cy, int cz);
void buscarPorTipo(CorpoCeleste*** mapa, int x, int y, int z, const char* tipo);
void gravarMapaEmArquivo(CorpoCeleste*** mapa, int x, int y, int z, const char* nomeArquivo);
void menu(CorpoCeleste*** mapa, int x, int y, int z);

int main() {
    int dimensaoX, dimensaoY, dimensaoZ;

    printf("Digite as dimensões do espaço (X Y Z): ");
    scanf("%d %d %d", &dimensaoX, &dimensaoY, &dimensaoZ);

    CorpoCeleste*** mapa = criarMapa(dimensaoX, dimensaoY, dimensaoZ);

    menu(mapa, dimensaoX, dimensaoY, dimensaoZ);

    liberarMapa(mapa, dimensaoX, dimensaoY);
    return 0;
}

CorpoCeleste*** criarMapa(int x, int y, int z) {
    CorpoCeleste*** mapa = (CorpoCeleste***)malloc(x * sizeof(CorpoCeleste**));
    for (int i = 0; i < x; i++) {
        mapa[i] = (CorpoCeleste**)malloc(y * sizeof(CorpoCeleste*));
        for (int j = 0; j < y; j++) {
            mapa[i][j] = (CorpoCeleste*)calloc(z, sizeof(CorpoCeleste));
        }
    }
    return mapa;
}

void liberarMapa(CorpoCeleste*** mapa, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            free(mapa[i][j]);
        }
        free(mapa[i]);
    }
    free(mapa);
}

void adicionarCorpoCeleste(CorpoCeleste*** mapa, int x, int y, int z, int cx, int cy, int cz, const char* nome, const char* tipo) {
    if (cx >= 0 && cx < x && cy >= 0 && cy < y && cz >= 0 && cz < z) {
        strcpy(mapa[cx][cy][cz].nome, nome);
        strcpy(mapa[cx][cy][cz].tipo, tipo);
        printf("%s do tipo %s adicionado em (%d, %d, %d).\n", nome, tipo, cx, cy, cz);
    } else {
        printf("Coordenadas inválidas!\n");
    }
}

void removerCorpoCeleste(CorpoCeleste*** mapa, int cx, int cy, int cz) {
    if (strlen(mapa[cx][cy][cz].nome) > 0) {
        printf("%s removido de (%d, %d, %d).\n", mapa[cx][cy][cz].nome, cx, cy, cz);
        memset(&mapa[cx][cy][cz], 0, sizeof(CorpoCeleste));
    } else {
        printf("Nenhum corpo celeste encontrado em (%d, %d, %d).\n", cx, cy, cz);
    }
}

void buscarPorCoordenadas(CorpoCeleste*** mapa, int cx, int cy, int cz) {
    if (strlen(mapa[cx][cy][cz].nome) > 0) {
        printf("Encontrado: %s do tipo %s em (%d, %d, %d).\n", mapa[cx][cy][cz].nome, mapa[cx][cy][cz].tipo, cx, cy, cz);
    } else {
        printf("Nenhum corpo celeste encontrado em (%d, %d, %d).\n", cx, cy, cz);
    }
}

void buscarPorTipo(CorpoCeleste*** mapa, int x, int y, int z, const char* tipo) {
    int encontrado = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                if (strcmp(mapa[i][j][k].tipo, tipo) == 0) {
                    printf("%s do tipo %s encontrado em (%d, %d, %d).\n", mapa[i][j][k].nome, tipo, i, j, k);
                    encontrado = 1;
                }
            }
        }
    }
    if (!encontrado) {
        printf("Nenhum corpo celeste do tipo %s encontrado.\n", tipo);
    }
}

void gravarMapaEmArquivo(CorpoCeleste*** mapa, int x, int y, int z, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para gravação!\n");
        return;
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                if (strlen(mapa[i][j][k].nome) > 0) {
                    fprintf(arquivo, "%s,%s,%d,%d,%d\n", mapa[i][j][k].nome, mapa[i][j][k].tipo, i, j, k);
                }
            }
        }
    }
    fclose(arquivo);
    printf("Mapa gravado no arquivo %s com sucesso.\n", nomeArquivo);
}

void menu(CorpoCeleste*** mapa, int x, int y, int z) {
    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar corpo celeste\n");
        printf("2. Remover corpo celeste\n");
        printf("3. Buscar por coordenadas\n");
        printf("4. Buscar por tipo\n");
        printf("5. Gravar mapa em arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int cx, cy, cz;
                char nome[50], tipo[20];
                printf("Digite as coordenadas (X Y Z): ");
                scanf("%d %d %d", &cx, &cy, &cz);
                printf("Digite o nome: ");
                scanf("%s", nome);
                printf("Digite o tipo (estrela ou planeta): ");
                scanf("%s", tipo);
                adicionarCorpoCeleste(mapa, x, y, z, cx, cy, cz, nome, tipo);
                break;
            }
            case 2: {
                int cx, cy, cz;
                printf("Digite as coordenadas (X Y Z): ");
                scanf("%d %d %d", &cx, &cy, &cz);
                removerCorpoCeleste(mapa, cx, cy, cz);
                break;
            }
            case 3: {
                int cx, cy, cz;
                printf("Digite as coordenadas (X Y Z): ");
                scanf("%d %d %d", &cx, &cy, &cz);
                buscarPorCoordenadas(mapa, cx, cy, cz);
                break;
            }
            case 4: {
                char tipo[20];
                printf("Digite o tipo (estrela ou planeta): ");
                scanf("%s", tipo);
                buscarPorTipo(mapa, x, y, z, tipo);
                break;
            }
            case 5: {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo: ");
                scanf("%s", nomeArquivo);
                gravarMapaEmArquivo(mapa, x, y, z, nomeArquivo);
                break;
            }
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);
}
