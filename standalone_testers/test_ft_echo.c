
#include "../includes/minishell.h"

int ft_echo(char **args)
{
    int i = 1;
    int j = 0;

    i = 1;  
    if (args[i] && (j = strcmp(args[i], "-n")) == 0)
        i = 2; /* Começa a imprimir a partir do primeiro argumento (args[1]) */

    ft_echo_print_arguments(args, i);
    if (j != 0)
    {
        printf("\n");  /* Imprime a nova linha no final */
        return (0);
    }
    return (1);
}

void ft_echo_print_arguments(char **args, int start_index)
{

    while (args[start_index])
    {
        printf("%s", args[start_index]);
        if (args[start_index + 1])
            printf("%c", ' ');
        start_index++;
    }
}

int main()
{
    char *args[] = {"-n", "Hello, World!", NULL};
    if (ft_echo(args) != 0)
        return (1);
    return (0);
}