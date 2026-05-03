#include "minishell.h"

static void heredoc_child(char *delimiter, int write_fd)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
        while (1)
        {
                write(1, "> ", 2);
                line = get_next_line(0);
                if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
						line[ft_strlen(line) - 1] = '\0';
				if (ft_strncmp(line, delimiter, delim_len) == 0)
				{
					free(line);
					break;
				}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	close(write_fd);
	exit(0);
}

int handle_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if(pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		setup_signals_child();
		heredoc_child(delimiter, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		return (-1);
	}
	return(fd[0]);
}