#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Función para imprimir el pid del proceso hijo
void print_pid() {
    printf("PID: %d\n", getpid());
}

int main() {
    pid_t pid_M, pid_A, pid_B;
    int status_M, status_A, status_B;

    // Crear proceso hijo M
    pid_M = fork();
    if (pid_M == 0) {
        // Este es el proceso hijo M
        sleep(3);
        print_pid();
        return 3;
    } else if (pid_M < 0) {
        // Error al crear el proceso hijo M
        printf("Error al crear proceso hijo M\n");
        exit(1);
    }

    // Crear proceso hijo A
    pid_A = fork();
    if (pid_A == 0) {
        // Este es el proceso hijo A
        sleep(10);
        print_pid();
        return 10;
    } else if (pid_A < 0) {
        // Error al crear el proceso hijo A
        printf("Error al crear proceso hijo A\n");
        exit(1);
    }

    // Crear proceso hijo B
    pid_B = fork();
    if (pid_B == 0) {
        // Este es el proceso hijo B
        print_pid();
        return 0;
    } else if (pid_B < 0) {
        // Error al crear el proceso hijo B
        printf("Error al crear proceso hijo B\n");
        exit(1);
    }

    // Este es el proceso padre
    // Esperar a que los procesos hijos terminen en orden M, A, B
    pid_t pid_waited;
    pid_waited = waitpid(pid_M, &status_M, 0);
    printf("Hijo con PID %d terminó correctamente con valor de retorno %d\n", pid_waited, WEXITSTATUS(status_M));
   
    pid_waited = waitpid(pid_A, &status_A, 0);
    printf("Hijo con PID %d terminó correctamente con valor de retorno %d\n", pid_waited, WEXITSTATUS(status_A));
   
    pid_waited = waitpid(pid_B, &status_B, 0);
    printf("Hijo con PID %d terminó correctamente con valor de retorno %d\n", pid_waited, WEXITSTATUS(status_B));

    return 0;
}
