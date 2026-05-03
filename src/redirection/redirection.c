#include "minishell.h"

static int	map_token_to_redir_type(t_token_type token, t_redir_type *type)
{
	if (token == TOKEN_REDIR_IN)
		*type = REDIR_IN;
	else if (token == TOKEN_REDIR_OUT)
		*type = REDIR_OUT;
	else if (token == TOKEN_APPEND)
		*type = REDIR_APPEND;
	else if (token == TOKEN_HEREDOC)
		*type = REDIR_HEREDOC;
	else
		return (-1);
	return (0);
}

int	redirection(t_cmd *cmd)
{
	t_redir		redir;
	t_redir_type	type;

	if (!cmd || !cmd->redir_file)
		return (0);
	if (map_token_to_redir_type(cmd->redir_type, &type) < 0)
	{
		g_exit_status = 2;
		return (-1);
	}
	redir.type = type;
	redir.file = cmd->redir_file;
	redir.next = NULL;
	return (apply_redirections(&redir));
}