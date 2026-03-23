/* ************************************************************************** */
/*                                                                            */
/*   read_input.c                                                             */
/*   src/read_input.c                                                         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Constrói o prompt com o directório actual.
   O parâmetro shell está reservado para expansões futuras (ex: mostrar
   g_exit_status no prompt). (void) evita -Werror,-Wunused-parameter.  */
char	*build_prompt(t_shell *shell)
{
	char	*cwd;
	char	*prompt;

	(void)shell;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("minishell> "));
	prompt = ft_strjoin(cwd, " $ ");
	free(cwd);
	if (!prompt)
		return (ft_strdup("minishell> "));
	return (prompt);
}

/* Retorna 1 se str só tem espaços/tabs/newlines, 0 caso contrário */
int	is_empty(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/* Liga as fases: lexer → parser → executor.
   Em modo DEBUG_LEXER esta função nunca é chamada (ver run_shell.c). */
void	process_input(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(input);
	if (!tokens)
		return ;
	cmds = parser(tokens);
	free_tokens(tokens);
	if (!cmds)
	{
		shell->exit_status = g_exit_status;
		return ;
	}
	free_cmds(cmds);
	shell->exit_status = g_exit_status;
}
