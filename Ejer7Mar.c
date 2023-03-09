#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

// Función para imprimir el pid y un número aleatorio generado

void print_pid_and_random() {
    printf("PID: %d, Random number: %d\n", getpid(), rand() % 100 + 1);
    exit(0);
} 


int main() {
    pid_t pid;
    int i, status, num_children = 3, num_success = 0;
    srand(time(NULL)); // Inicializar el generador de números aleatorios
   
    // Crear 3 procesos hijos
    for (i = 0; i < num_children; i++) {
        pid = fork();
        
        if (pid == 0) {
            // Este es el proceso hijo
            print_pid_and_random();
        } else if (pid < 0) {
            // Error al crear el proceso hijo
            printf("Error al crear proceso hijo\n");
            exit(1);
        }
    }
   
    // Este es el proceso padre
    // Esperar a que todos los procesos hijos terminen
    for (i = 0; i < num_children; i++) {
        pid = wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("Hijo con PID %d terminó correctamente\n", pid);
            num_success++;
        }
    }
   
    // Imprimir el número total de procesos hijos que terminaron correctamente
    printf("Total de procesos hijos que terminaron correctamente: %d\n", num_success);
   
    return 0;
}

