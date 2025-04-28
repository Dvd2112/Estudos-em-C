#include <stdio.h>

#include <stdlib.h>

#define MAX_VETOR [10]

int pares[MAX_VETOR];
int m[1][10];


void vetor(){
int ind, val = 10;
ind = 1;
pares [0] = 10;
while (ind <11) {
pares[ind] = val + 2;
val = val + 2;
ind++;
}
}

void matriz () {

int indL = 0, indC = 0, x = 0;

while (x < 11) {

m [indL][indC] = pares[x];

x++;
}}

int main() { 
    int x = 0 , y = 0 , lm =0, cm=0;

int op = 0;


while (op != 3) {  
    printf("menu"); 
    printf("(1) vetor"); 
    printf("(2) matriz"); 
    printf("(3) sair");  
    printf("informe a opcao"); 
    scanf("%d", &op);  
    if (op != 3) {
        if (p = 1)
        vetor()
        if (op = 2)
        matriz()
        matriz(); 
        }else{
            for ( x = 0; x < 11; x++) {

printf("vetor Posicao %d eh %d", x, pares[x]);

}


for(y = 0, y<11; y++) {

printf("a mataiz na Linha %d e Coluna %d eh %d", lm, cm, m[lm][cm]);

cm++;
}
}
}
}
