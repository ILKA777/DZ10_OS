#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int receiver_pid;

void confirmation_handler(int signum) {
    // Ничего не делаем, просто ловим подтверждение
}

int main() {
    signal(SIGUSR1, confirmation_handler);

    printf("Sender PID: %d\n", getpid());
    printf("Input receiver PID: ");
    scanf("%d", &receiver_pid);

    int number;
    printf("Input decimal integer number: ");
    scanf("%d", &number);

    for (int i = 0; i < 32; i++) {
        int bit = (number >> i) & 1;
        if (bit == 0) {
            kill(receiver_pid, SIGUSR1);
        } else {
            kill(receiver_pid, SIGUSR2);
        }

        pause(); // Ждем подтверждения
    }

    kill(receiver_pid, SIGINT); // Завершаем приемник
    return 0;
}
