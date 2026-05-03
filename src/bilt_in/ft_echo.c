#include "minishell.h"

int ft_echo(char **args)
{
    int i = 1;
    int newline = 1;

    while (args[i] && is_n_flag(args[i]))
    {
        newline = 0;
        i++;
    }

    ft_echo_print_arguments(args, i);

    if (newline)
        ft_putstr_fd("\n", 1);

    return (0);
}

int is_n_flag(char *str)
{
    int i = 1;

    if (!str || str[0] != '-')
        return (0);
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (i > 1);
}

void ft_echo_print_arguments(char **args, int start_index)
{

    while (args[start_index])
    {
        ft_putstr_fd(args[start_index], 1);
        if (args[start_index + 1])
            ft_putstr_fd(" ", 1);
        start_index++;
    }
}