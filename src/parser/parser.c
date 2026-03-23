#include "minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	parser_error(const char *msg)
{
	write(STDERR_FILENO, "minishell: parser: ", 18);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = 2;
	return (-1);
}

static int	args_len(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_args(cmds->args);
		free(cmds->redir_file);
		free(cmds);
		cmds = next;
	}
}

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

static int	append_cmd(t_cmd **head, t_cmd *new_cmd)
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

static t_cmd	*parse_one_command(t_token **cur)
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

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_token	*cur;
	t_cmd	*cmd;

	head = NULL;
	cur = tokens;
	if (!cur)
		return (NULL);
	while (cur)
	{
		if (cur->type == TOKEN_PIPE)
			return (parser_error("unexpected pipe"), free_cmds(head), NULL);
		cmd = parse_one_command(&cur);
		if (!cmd)
			return (free_cmds(head), NULL);
		append_cmd(&head, cmd);
		if (cur && cur->type == TOKEN_PIPE)
		{
			cur = cur->next;
			if (!cur)
				return (parser_error("trailing pipe"), free_cmds(head), NULL);
		}
	}
	return (head);
}
