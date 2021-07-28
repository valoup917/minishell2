/*
** EPITECH PROJECT, 2021
** priorities.c
** File description:
** .
*/

#include <fcntl.h>
#include "mysh.h"

void separate_semi(char **argv, List *my_env)
{
    char **tmp = malloc(sizeof(char *) * 20);
    int a = 0;
    for (int i = 0; argv[i]; i++) {

        if (my_strcmp(argv[i], ";") == 0) {
            tmp[a + 1] = NULL;
            executable(tmp, my_env);
            a = 0;
            tmp = malloc(sizeof(char *) * 20);
        }
        else {
            tmp[a] = argv[i];
            a++;
        }

    }
    tmp[a + 1] = NULL;
    executable(tmp, my_env);
}

char *wich_file(char **argv)
{
    for (int i = 0; argv[i]; i++) {
        if (!my_strcmp(argv[i], ">"))
            return argv[i + 1];
        if (!my_strcmp(argv[i], ">>"))
            return argv[i + 1];
        if (!my_strcmp(argv[i], "<"))
            return argv[i + 1];
    }
    return my_strdup("file");
}

void redirection(char **argv, List *my_env, int a)
{
    char **tmp = malloc(sizeof(char *) * 10);
    int file = 0;
    int stdout_real = dup(STDOUT_FILENO);

    if (a == 1)
        file = open(wich_file(argv), O_WRONLY | O_CREAT, 0666);
    else if (a == 2)
        file = open(wich_file(argv), O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (file == -1)
        return;
    dup2(file, STDOUT_FILENO);
    close(file);
    for (int i = 0; argv[i]; i++) {
        if (!my_strcmp(argv[i], ">") || !my_strcmp(argv[i], ">>")) {
            tmp[i + 1] = NULL;
            executable(tmp, my_env);
        } else
            tmp[i] = argv[i];
    }
    dup2(stdout_real, STDOUT_FILENO);
}

void input_redirect(char **argv)
{
    int size = 0;
    char *line = NULL;
    size_t len = 0;

    my_putstr(">");
    while ((size = getline(&line, &len, stdin)) != -1) {
        line[size - 1] = '\0';
        if (my_strcmp(wich_file(argv), line) == 0)
            break;
        my_putstr(">");
    }
}