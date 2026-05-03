#include "minishell.h"

void	executer(t_shell *shell, t_cmd *cmds)
{
	if (!cmds)
		return ;
	shell->exit_status = run_cmd(cmds, shell->env);
}