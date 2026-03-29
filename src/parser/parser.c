#include "minishell.h"

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
