#include <stdio.h>
#include <unistd.h>    
#include <termios.h>   
#include <fcntl.h>     

#define MAX_VOLTAS 5


void configurar_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


void restaurar_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


char getch() {
    return getchar();
}

int main() {
    int horas = 0, minutos = 0, segundos = 0;
    int rodando = 1; // Indica se o cronômetro está rodando
    int voltas[MAX_VOLTAS][3]; // Armazena as voltas: [hora, minuto, segundo]
    int num_voltas = 0;
    char tecla;

    configurar_terminal(); 

    printf("Bem-vindo ao cronômetro!\n");
    printf("Pressione qualquer tecla para parar ou computar uma volta (máximo de 5 voltas).\n");
    printf("Pressione 'q' para sair.\n");

    while (1) {
        
        if (rodando) {
            printf("\r%02d:%02d:%02d", horas, minutos, segundos);
            fflush(stdout);
            sleep(1);

            
            segundos++;
            if (segundos == 60) {
                segundos = 0;
                minutos++;
            }
            if (minutos == 60) {
                minutos = 0;
                horas++;
            }
        }

       
        if (kbhit()) {
            tecla = getch(); 

            if (tecla == 'q') { 
                rodando = 0; 
                printf("\nCronômetro encerrado.\n");
                break;
            }

            if (rodando) {
                
                rodando = 0;
                printf("\nCronômetro pausado.\n");
            } else {
                
                if (num_voltas < MAX_VOLTAS) {
                    voltas[num_voltas][0] = horas;
                    voltas[num_voltas][1] = minutos;
                    voltas[num_voltas][2] = segundos;
                    num_voltas++;
                    printf("\nVolta %d registrada: %02d:%02d:%02d\n", num_voltas, horas, minutos, segundos);
                } else {
                    printf("\nLimite de 5 voltas alcançado.\n");
                }

                rodando = 1;
                printf("Cronômetro retomado.\n");
            }
        }
    }

    restaurar_terminal(); 
    
    if (num_voltas > 0) {
        printf("\nResumo das voltas:\n");
        for (int i = 0; i < num_voltas; i++) {
            printf("Volta %d: %02d:%02d:%02d\n", i + 1, voltas[i][0], voltas[i][1], voltas[i][2]);
        }
    }

    return 0;
}
