/*
** EPITECH PROJECT, 2021
** priorities.c
** File description:
** .
*/

#include "mysh.h"

int check_part2(char **argv, List *my_env)
{
    for (int i = 0; argv[i];i++) {
        if (my_strcmp(argv[i], "<<") == 0) {
            input_redirect(argv);
            return 1;
        }
        if (my_strcmp(argv[i], "<") == 0) {
            file_redirect(argv, my_env);
            return 1;
        }
        if (my_strcmp(argv[i], "|") == 0) {
            handle_pipe(argv, my_env);
            return 1;
        }
    }
    return 0;
}

int check_ms2(char **argv, List *my_env)
{
    for (int i = 0; argv[i];i++) {
        if (my_strcmp(argv[i], ";") == 0) {
            separate_semi(argv, my_env);
            return 1;
        }
        if (my_strcmp(argv[i], ">>") == 0) {
            redirection(argv, my_env, 2);
            return 1;
        }
        if (my_strcmp(argv[i], ">") == 0) {
            redirection(argv, my_env, 1);
            return 1;
        }
        if (check_part2(argv, my_env))
            return 1;
    }
    return 0;
}