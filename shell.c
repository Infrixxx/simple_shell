#include "main.h"

int main() {
    char buffer[BUFFER_SIZE];
    char prompt[] = "#cisfun$ ";

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
        } else if (pid == 0) {
            if (execlp(buffer, buffer, (char *)NULL) == -1) {
                perror(buffer);
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            wait(&status);
        }
    }

    return 0;
}
