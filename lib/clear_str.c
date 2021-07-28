/*
** EPITECH PROJECT, 2021
** clear_str.c
** File description:
** .
*/

#include <mysh.h>

char *clear_str(const char *str)
{
    char *new = malloc(sizeof(char) * my_strlen(str)+50);
    unsigned int a = 0;
    int p = 0;

    for (int i = 0;str[i];i++) {
        while ((str[i] == ' ' || str[i] == '\t') && p == 0) {
            i++;
        }
        p = 1;
        if (str[i] == '\t' && (str[i - 1] == '\t' || str[i - 1] == ' ')) {
            continue;
        }
        else {
            if (i != 0 && (str[i] == ';' || str[i] == '>' || str[i] == '<'
            || str[i] == '|')
            && str[i - 1] != ' ' && str[i - 1] != '<' && str[i - 1] != '>'
            && str[i - 1] != '|') {
                new[a] = ' ';
                new[a + 1] = str[i];
                a++;
            }
            if (str[i + 1] != '\0' && (str[i] == ';' || str[i] == '>'
            || str[i] == '<' || str[i] == '|') && str[i + 1] != ' '
            && str[i + 1] != '<'
            && str[i + 1] != '>' && str[i + 1] != '|') {
                new[a] = str[i];
                new[a+ 1] = ' ';
                a += 2;
                continue;
            }
            else if (str[i] == '\t')
                new[a] = ' ';
            else
                new[a] = str[i];
            a++;
        }
    }
    new[a] = '\0';
    return new;
}