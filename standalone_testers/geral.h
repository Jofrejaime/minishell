# ifndef GERAL_H
# define GERAL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>


void	free_array(char	**dirs);
char	*find_in_path(char *cmd, char **envp);
int run_cmd(char *cmd_full, char **argv, char **envp, int timeout);

#endif
