/*
** EPITECH PROJECT, 2021
** path
** File description:
** .
*/

#include <mysh.h>

int find_path_pos(char **env, List *my_env)
{
    int x = 0;

    for (;env[x][0] != 'P' || env[x][1] != 'A' || env[x][2] != 'T'
    || env[x][3] != 'H' || env[x][4] != '='; x++);
    if (my_strlen(env[x]) <= 5) {
        my_env->path = NULL;
        return -1;
    }
    return x;
}

void path_add(List *my_env, char **env)
{
    int x = find_path_pos(env, my_env);
    int count = 0;
    char *token;
    char *tmp;
    int w = 0;

    if (x < 0)
        return;
    token = env[x] + 5;
    for (int n = 0; token[n] != '\0'; n++)
        if (token[n] == ':')
            count++;
    my_env->path = malloc(sizeof(char *) * (count + 2));
    for (; w <= count; w++) {
        tmp = strtok(my_strdup(token), ":");
        token = token + my_strlen(tmp);
        my_env->path[w] = tmp;
        my_env->path[w][my_strlen(tmp)] = '\0';
        tmp = strtok(NULL, " ");
    }
    my_env->path[w] = NULL;
}