#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    int id;
    char descricao[256];
    char data[20];
    char status[20]; 
    char registradoPor[50]; 
} Incidente;



Incidente* adicionarIncidente(Incidente* incidentes, int* tamanho, const char* usuarioAtual);
void atualizarStatus(Incidente* incidentes, int tamanho);
Incidente* removerIncidente(Incidente* incidentes, int* tamanho);
void consultarIncidentePorID(Incidente* incidentes, int tamanho);
void registrarAlteracaoEmArquivo(const char* operacao, Incidente incidente);
void menu(const char* usuarioAtual);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Protótipos
void loginSistema();

int autenticarUsuario(const char* login, const char* senha);
void registrarUsuario(const char* login, const char* senha);

void loginSistema() {
    int opcao;
    char login[50];
    char senha[50];

    printf("--- Sistema de Login ---\n");
    printf("1. Entrar\n");
    printf("2. Registrar novo usuário\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    printf("Digite o login: ");
    scanf("%s", login);
    printf("Digite a senha: ");
    scanf("%s", senha);

    if (opcao == 1) {
        if (autenticarUsuario(login, senha)) {
            printf("Login bem-sucedido! Bem-vindo(a), %s.\n", login);
        } else {
            printf("Credenciais inválidas. Tente novamente.\n");
            exit(1); 
        }
    } else if (opcao == 2) {
        registrarUsuario(login, senha);
        printf("Usuário registrado com sucesso!\n");
    } else {
        printf("Opção inválida. Saindo...\n");
        exit(1);
    }
}

int autenticarUsuario(const char* login, const char* senha) {
    FILE* arquivo = fopen("usuarios.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários. Certifique-se de que há usuários registrados.\n");
        return 0;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char loginArq[50], senhaArq[50];
        sscanf(linha, "%s %s", loginArq, senhaArq); // Lê login e senha da linha

        if (strcmp(login, loginArq) == 0 && strcmp(senha, senhaArq) == 0) {
            fclose(arquivo);
            return 1; 
        }
    }

    fclose(arquivo);
    return 0; 
}

void registrarUsuario(const char* login, const char* senha) {
    FILE* arquivo = fopen("usuarios.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de usuários para escrita.\n");
        exit(1);
    }

    fprintf(arquivo, "%s %s\n", login, senha); 
    fclose(arquivo);
}

int main() {
    char usuarioAtual[50];

    printf("Digite seu nome de usuário para login: ");
    scanf("%s", usuarioAtual);

    loginSistema(); 

    menu(usuarioAtual); 
    return 0;
}


Incidente* adicionarIncidente(Incidente* incidentes, int* tamanho, const char* usuarioAtual) {
    incidentes = (Incidente*)realloc(incidentes, (*tamanho + 1) * sizeof(Incidente));

    Incidente novo;
    novo.id = (*tamanho == 0) ? 1 : incidentes[*tamanho - 1].id + 1;
    printf("Digite a descrição do incidente: ");
    getchar(); 
    fgets(novo.descricao, 256, stdin);
    novo.descricao[strcspn(novo.descricao, "\\n")] = 0; 

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(novo.data, "%02d-%02d-%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    strcpy(novo.status, "Aberto");
    strncpy(novo.registradoPor, usuarioAtual, 50); 

    incidentes[*tamanho] = novo;
    (*tamanho)++;

    registrarAlteracaoEmArquivo("Adicionado", novo);
    printf("Incidente registrado com ID %d.\n", novo.id);

    return incidentes;
}

void atualizarStatus(Incidente* incidentes, int tamanho) {
    int id;
    printf("Digite o ID do incidente a ser atualizado: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (incidentes[i].id == id) {
            printf("Status atual: %s\n", incidentes[i].status);
            printf("Digite o novo status (Aberto, Em andamento, Resolvido): ");
            getchar(); 
            fgets(incidentes[i].status, 20, stdin);
            incidentes[i].status[strcspn(incidentes[i].status, "\n")] = 0; 

            registrarAlteracaoEmArquivo("Atualizado", incidentes[i]);
            printf("Status do incidente ID %d atualizado para: %s\n", id, incidentes[i].status);
            return;
        }
    }
    printf("Incidente com ID %d não encontrado.\n", id);
}

Incidente* removerIncidente(Incidente* incidentes, int* tamanho) {
    int id;
    printf("Digite o ID do incidente a ser removido: ");
    scanf("%d", &id);

    for (int i = 0; i < *tamanho; i++) {
        if (incidentes[i].id == id) {
            registrarAlteracaoEmArquivo("Removido", incidentes[i]);

            for (int j = i; j < *tamanho - 1; j++) {
                incidentes[j] = incidentes[j + 1];
            }

            (*tamanho)--;
            incidentes = (Incidente*)realloc(incidentes, *tamanho * sizeof(Incidente));
            printf("Incidente com ID %d removido.\n", id);
            return incidentes;
        }
    }
    printf("Incidente com ID %d não encontrado.\n", id);
    return incidentes;
}

void consultarIncidentePorID(Incidente* incidentes, int tamanho) {
    int id;
    printf("Digite o ID do incidente a ser consultado: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (incidentes[i].id == id) {
            printf("\n--- Detalhes do Incidente ---\n");
            printf("ID: %d\n", incidentes[i].id);
            printf("Descrição: %s\n", incidentes[i].descricao);
            printf("Data: %s\n", incidentes[i].data);
            printf("Status: %s\n", incidentes[i].status);
            printf("Registrado por: %s\n", incidentes[i].registradoPor); 
            return;
        }
    }
    printf("Incidente com ID %d não encontrado.\n", id);
}

void registrarAlteracaoEmArquivo(const char* operacao, Incidente incidente) {
    FILE* arquivo = fopen("historico_incidentes.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }

    fprintf(arquivo, "%s - ID: %d, Descrição: %s, Data: %s, Status: %s\n", operacao, incidente.id, incidente.descricao, incidente.data, incidente.status);
    fclose(arquivo);
}

void menu(const char* usuarioAtual) {
    Incidente* incidentes = NULL;
    int tamanho = 0;
    int opcao;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar incidente\n");
        printf("2. Atualizar status de incidente\n");
        printf("3. Remover incidente\n");
        printf("4. Consultar incidente por ID\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incidentes = adicionarIncidente(incidentes, &tamanho, usuarioAtual);
                break;
            case 2:
                atualizarStatus(incidentes, tamanho);
                break;
            case 3:
                incidentes = removerIncidente(incidentes, &tamanho);
                break;
            case 4:
                consultarIncidentePorID(incidentes, tamanho);
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    free(incidentes);
}
