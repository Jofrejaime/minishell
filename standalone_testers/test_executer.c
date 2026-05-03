#include "minishell.h"

/*gcc -Wall -Wextra -I ../includes -o test_exec \
    test_executer.c \
    ../src/executer/geral.c \
    ../mini_libft/libft.a
    
    */

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (0);

	int i = 1;
	int j = 0;
	char *cmd;
	char *cmd_full;
	char **args = malloc(sizeof(char *)*10);
	
	while (argv[i])
	{
		cmd = argv[i];
		cmd_full = find_in_path(cmd, envp);
		if (!cmd_full)
		{
			printf("command not found: %s %s\n", cmd, argv[i]);
			return (1);
		}
		j = 0;
		i++;
		args[j++] = cmd;
		while(argv[i] && j < 10 && argv[i][0] != '|')
		{
			args[j] = argv[i];
			i++;
			j++;
		}
		args[j] = NULL;
		run_cmd(cmd_full, args, envp, 3);
		if (argv[i] && argv[i][0] == '|')
		i++;
	}
	return (0);
}
