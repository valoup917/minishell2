/*
** EPITECH PROJECT, 2021
** priorities.c
** File description:
** .
*/

#include <fcntl.h>
#include "mysh.h"

static int element_nbr(char **argv)
{
    int i = 0;

    for (; argv[i]; i++);
    return i + 1;
}

static void do_pipe(char **argv, List *my_env)
{
    if (my_bultins(argv[0], my_env, argv) == 0)
        executable(argv, my_env);
}

void handle_pipe(char **argv, List *my_env)
{
    char **tmp = malloc(sizeof(char *) * element_nbr(argv));
    int count = 0;
    int fd[2];
    int stdout_real = dup(STDOUT_FILENO);
    int stdin_real = dup(STDIN_FILENO);

    if (pipe(fd) == -1) {
        perror("probleme pipe");
        return;
    }
    for (int i = 0; argv[i]; i++) {
        if (!my_strcmp(argv[i], "|")) {
            tmp[count] = NULL;
            count = 0;
            if (fork() == 0) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                do_pipe(tmp, my_env);
                dup2(stdout_real, STDOUT_FILENO);
            }
        } else {
            tmp[count] = argv[i];
            count++;
        }
    }
    tmp[count] = NULL;
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    do_pipe(tmp, my_env);
    close(fd[0]);
    dup2(stdin_real, STDIN_FILENO);
}

void file_redirect(char **argv, List *my_env)
{
    char **tmp = malloc(sizeof(char *) * element_nbr(argv));
    char *file = wich_file(argv);
    int stdin_real = dup(STDIN_FILENO);
    int fd = 0;

    fd = open(file, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
    for (int i = 0; argv[i]; i++) {
        if (!my_strcmp(argv[i], "<")) {
            tmp[i + 1] = NULL;
            do_pipe(tmp, my_env);
        } else
            tmp[i] = argv[i];
    }
    dup2(stdin_real, STDIN_FILENO);
}