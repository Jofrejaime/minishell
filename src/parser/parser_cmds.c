#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir_type = TOKEN_WORD;
	cmd->redir_file = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	append_arg(t_cmd *cmd, const char *value)
{
	int		count;
	char	**new_args;
	int		i;

	count = args_len(cmd->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (-1);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(value);
	if (!new_args[count])
	{
		free(new_args);
		return (-1);
	}
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (0);
}

static int	parse_redirection(t_cmd *cmd, t_token **cur)
{
	t_token	*next;

	next = (*cur)->next;
	if (!next || next->type != TOKEN_WORD)
		return (parser_error("redirection without target"));
	free(cmd->redir_file);
	cmd->redir_type = (*cur)->type;
	cmd->redir_file = ft_strdup(next->value);
	if (!cmd->redir_file)
		return (-1);
	*cur = next->next;
	return (0);
}

int	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new_cmd;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	return (0);
}

t_cmd	*parse_one_command(t_token **cur)
{
	t_cmd	*cmd;
	int		has_content;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	has_content = 0;
	while (*cur && (*cur)->type != TOKEN_PIPE)
	{
		if ((*cur)->type == TOKEN_WORD)
		{
			if (append_arg(cmd, (*cur)->value) < 0)
				return (free_cmds(cmd), NULL);
			has_content = 1;
			*cur = (*cur)->next;
		}
		else if (is_redirection((*cur)->type))
		{
			if (parse_redirection(cmd, cur) < 0)
				return (free_cmds(cmd), NULL);
			has_content = 1;
		}
		else
			return (parser_error("unexpected token"), free_cmds(cmd), NULL);
	}
	if (!has_content)
		return (parser_error("empty command"), free_cmds(cmd), NULL);
	return (cmd);
}

