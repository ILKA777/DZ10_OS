#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int transmitter_pid;
int received_number = 0;
int current_bit = 0;

void receive_bit_0(int signum) {
    received_number |= (0 << current_bit);
    current_bit++;
    kill(transmitter_pid, SIGUSR1); // Подтверждение
}

void receive_bit_1(int signum) {
    received_number |= (1 << current_bit);
    current_bit++;
    kill(transmitter_pid, SIGUSR1); // Подтверждение
}

void finish_reception(int signum) {
    printf("Result : %d\n", received_number);
    exit(0);
}

int main() {
    signal(SIGUSR1, receive_bit_0);
    signal(SIGUSR2, receive_bit_1);
    signal(SIGINT, finish_reception);

    printf("Receiver PID: %d\n", getpid());
    printf("Input sender PID: ");
    scanf("%d", &transmitter_pid);

    while (1) {
        pause(); // Ждем сигналов
    }

    return 0;
}
