/*
** EPITECH PROJECT, 2021
** manage cd
** File description:
** .
*/

#include <mysh.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void cd_one_arg(List *my_env)
{
    char *str = home_env(my_env);

    if (!str) {
        str = malloc(sizeof(char) * 2);
        my_strcpy(str, ".");
    }
    move_old(my_env);
    if (chdir(str) == -1)
        my_env->exit = 1;
    else
        my_env->exit = 0;
    return;
}

static void check_stat(char *str)
{
    struct stat sb;
    stat(str, &sb);

    if (stat(str, &sb) == -1) {
        write(2, str, my_strlen(str));
        write(2, ": No such file or directory.\n", 29);
        return;
    } else if (!S_ISDIR(sb.st_mode)) {
        write(2, str, my_strlen(str));
        write(2, ": Not a directory.\n", 19);
        return;
    }
}

static void cd_two_arg(char **argv, List *my_env)
{
    char *str;

    check_stat(argv[1]);
    if (my_strcmp(argv[1], "-") == 0) {
        str = old_pwd(my_env);
        move_old(my_env);
        chdir(str);
        my_env->exit = 0;
        return;
    }
    move_old(my_env);
    if (my_strcmp(argv[1], "~") == 0)
        chdir(home_env(my_env));
    else if (chdir(argv[1]) == -1)
        my_env->exit = 1;
    else
        my_env->exit = 0;
}

void cd_cmd(char **argv, List *my_env)
{
    int argc = count_arg(argv);

    if (argc > 2) {
        my_putstr("cd: too many arguments\n");
        my_env->exit = 1;
        return;
    }
    if (argc == 1)
        cd_one_arg(my_env);
    else if (argc == 2)
        cd_two_arg(argv, my_env);
}