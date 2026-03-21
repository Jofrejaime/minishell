#include "minishell.h"

void    handle_eof(t_shell *shell)
{
    if (isatty(STDIN_FILENO))           /* só imprime "exit" em modo interactivo */
        write(STDOUT_FILENO, "exit\n", 5);
    free_shell(shell);
    exit(g_exit_status);
}

void    free_shell(t_shell *shell)
{
    if (shell->env)
        free_env(shell->env);
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    rl_clear_history();   /* liberta o histórico interno do readline */
}

void    free_env(char **env)
{
    int i;

    if (!env)
        return ;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}
