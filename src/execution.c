/*
** EPITECH PROJECT, 2021
** execution
** File description:
** .
*/

#include <mysh.h>

int check_path(char **path, char *str, List *my_env)
{
    if (!path) {
        my_putstr(my_strcat(str, ": Command not found.\n"));
        my_env->exit = 1;
        return 1;
    }
    return 0;
}

void executable(char **argv, List *my_env)
{
    char *tmp = malloc(sizeof(char)*500);
    char *test = malloc(sizeof(char)*500);
    char **new = my_env->path;

    if (check_path(new, argv[0], my_env))
        return;
    if (access(argv[0], X_OK) == 0) {
        processe(argv[0], my_env->env, argv, &(my_env->exit));
        return;
    } for (int i = 0; new[i]; i++) {
        tmp = my_strcat(my_strdup("/"), my_strdup(argv[0]));
        test = my_strcat(my_strdup(new[i]), tmp);
        if (access(test, X_OK) == 0) {
            processe(test, my_env->env, argv, &(my_env->exit));
            return;
        }
    }
    my_putstr(my_strcat(argv[0], my_strdup(": Command not found.\n")));
    my_env->exit = 1;
}

void processe(char *path, char **env, char **argv, int *a)
{
    *a = 0;
    pid_t pid = fork();
    int	status;

    if (pid == -1)
        return;
    if (pid == 0)
        execve(path, argv, env);
    else
        waitpid(pid, &status, 0);
}