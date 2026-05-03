#include "minishell.h"

static void child_process_execve(t_cmd *cmds, char **envp, int prev_fd, int fd[2])
{
        if (prev_fd != -1)
        {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
        }
        if (cmds->next)
        {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
        }
        char *cmd_full = find_in_path(cmds->args[0], envp);
        if (!cmd_full)
        {
                printf("command not found: %s\n", cmds->args[0]);
                exit(127);
        }
        execve(cmd_full, cmds->args, envp);
        perror("execve");
        exit(127);
}
static int commands_iteration(t_cmd *cmds, char **envp, int *prev_fd, int fd[2])
{
        pid_t	pid;

        if (cmds->next && pipe(fd) == -1)
		perror("pipe");
        pid = fork();
        if (pid == -1)
        {
                perror("fork");
                return (0);
        }
        if (pid == 0)
                child_process_execve(cmds, envp, *prev_fd, fd);
        if (*prev_fd != -1)
                close(*prev_fd);
        if (cmds->next)
        {
                close(fd[1]);
                *prev_fd = fd[0];
        }
        return (1);
}
int	run_cmd(t_cmd *cmds, char **envp)
{
	int		fd[2];
	int		prev_fd = -1;
	int		status = 0;

	while (cmds)
	{
		if (is_builtin(cmds->args[0]))
		{
			if (!execute_builtin(cmds))		
				return (1);
		}
		else
		if (!commands_iteration(cmds, envp, &prev_fd, fd))
                        return (1);
                cmds = cmds->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

char	*find_in_path(char *cmd, char **envp)
{
	int	i;
	char *path_env;
	char **dirs;
	char *full;
	char *tmp;

	i = 0;
	path_env = NULL;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while(dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
		{
			free_array(dirs);
			return (full);
		}
		free(full);
		i++;
	}
	free_array(dirs);
	return (NULL);
}
