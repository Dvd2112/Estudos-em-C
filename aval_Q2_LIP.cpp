/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NOME [3];

typedef struct DADOS{
    int ra;
    char nome[MAX_NOME][50];
}
int main(){
    int op = 0;
    while(op != 3){
        printf("+_+_+menu principal+_+_+ \n");
        printf("[1] registrar\n");
        printf("[2] apresentar\n");
        printf("[3] sair\n");
        printf("+_+_+menu principal+_+_+\n");
        scanf("%d", &op);
        
        if(op !=3){
            if(op = 1)
            preencherDados();
            if(op = 2)
            apresentarDados();
        }
    }
        return 0;
    }
    
    

int qntd;
DADOS registro[qntd];

void preencherDados(){
    qntd = 0;
    for(qntd = 0;qntd < 3; qntd){
        lbt();
        printf("digite o ra");
        scanf("%d", registro[qntd].ra);
        printf("digite o nome");
        scanf("%d", registro[qntd].nome);
    }
    printf("registros feitos");
}

void apresentarDados(){
    int x = 0;
    
    if (registro[0].ra == 0){
        printf("não existem registros");
    }
    else{
        while(x < 3){
            printf("registro %i, ra %d, nome %[^\n]", x, registro[x].ra , registro[x].nome);
            x++;
        }
    }
}

void lbt(){
    int c = o;
    while(getchar() != '\n' && c != EOF0){}
}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOME 3

typedef struct {
    int ra;
    char nome[50];
}DADOS;

DADOS registro[MAX_NOME];

void preencherDados() {
    int x;
    for (int x = 0; x < 3; x++) {
        printf("digite o ra:");
        scanf("%d", &registro[x].ra);

        printf("digite o nome:");
        scanf("%[^\n]", registro[x].nome);
    }
    printf("registros feitos\n");
}

void apresentarDados() {
    int x = 0;
    
    if (registro[0].ra == 0) {
        printf("nao existem registros.\n");
    }
    else{
        while (x < 3) {
        printf("Registro %d ra: %d  nome: %s \n", x + 1, registro[x].ra, registro[x].nome);
        x++;
    }
    }
}


int main(){
    int op = 0;

    while (op != 3) {
        printf("+_+_+ menu principal +_+_+\n");
        printf("[1] Registrar\n");
        printf("[2] Apresentar\n");
        printf("[3] Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        if(op!=3){
        if (op == 1) 
            preencherDados();
        if (op == 2) 
            apresentarDados();
        }
    }
    return 0;
}
