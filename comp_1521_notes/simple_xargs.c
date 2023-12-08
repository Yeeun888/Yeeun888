#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <string.h>

extern char **environ;

int main(int argc, char* argv[]) {
    pid_t process_pid;
    char *program_name = strrchr(argv[1], '/') + 1;
    char *arguments[3] = {program_name, NULL, NULL};
    arguments[1] = malloc(sizeof(char) * 1024);

    while(scanf("%s", arguments[1]) != -1) {
        posix_spawn(&process_pid, argv[1], NULL, NULL, arguments, environ);
    }
}