#include "minishell.h"

int init_shell(t_shell *shell, char **envp)
{
    ft_memset(shell, 0, sizeof(t_shell));
    shell->env = init_env(envp);
    if (!shell->env)
        return (1);
    shell->exit_status = 0;
    return (0);
}

char    **init_env(char **envp)
{
    int     count;
    char    **env;
    int     i;

    count = 0;
    while (envp[count])
        count++;
    env = malloc(sizeof(char *) * (count + 1));
    if (!env)
        return (NULL); 
    i = 0;
    while (i < count)
    {
        env[i] = ft_strdup(envp[i]);
        if (!env[i])
        {
            free_env(env);   /* liberta o que já foi alocado */
            return (NULL);
        }
        i++;
    }
    env[i] = NULL;
    return (env);
}

char    *ft_getenv(char **env, const char *name)
{
    int     len;
    int     i;

    len = ft_strlen(name);
    i = 0;
    while (env[i])
    {
        /* compara "HOME=" com o início da string */
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1);  /* devolve só o valor */
        i++;
    }
    return (NULL);
}