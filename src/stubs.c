/* ************************************************************************** */
/*                                                                            */
/*   stubs.c                                                                  */
/*   src/stubs.c                                                              */
/*                                                                            */
/*   Fases 3 e 5 temporárias — permitem compilar sem parser/executor.         */
/*   APAGA este ficheiro quando implementares a Fase 3 (parser).              */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tokens)
{
	(void)tokens;
	return (NULL);
}

int	executor(t_shell *shell, t_cmd *cmds)
{
	(void)shell;
	(void)cmds;
	return (0);
}

void	free_cmds(t_cmd *cmds)
{
	(void)cmds;
}
