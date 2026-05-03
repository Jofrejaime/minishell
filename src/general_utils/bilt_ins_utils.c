#include "minishell.h"

int is_builtin(char *cmd)
{
    if (cmd == NULL)
        return (0);
    return (strcmp(cmd, "echo") == 0 || \
            strcmp(cmd, "cd") == 0 || \
            strcmp(cmd, "pwd") == 0 || \
            strcmp(cmd, "export") == 0 || \
            strcmp(cmd, "unset") == 0 || \
            strcmp(cmd, "env") == 0 || \
            strcmp(cmd, "exit") == 0); 
}

int execute_builtin(t_cmd *cmd)
{
    if (strcmp(cmd->args[0], "echo") == 0)
        return (ft_echo(cmd->args));
    return (0);
}