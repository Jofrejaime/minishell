#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = ft_strdup(value);
	if (!tok->value)
	{
		free(tok);
		return (NULL);
	}
	tok->next = NULL;
	return (tok);
}

void	token_list_add(t_token **head, t_token *new)
{
	t_token	*cur;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		next;

	head = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			next = handle_operator(&head, input, i);
		else if (input[i] == '\'')
			next = handle_single_quote(&head, input, i);
		else if (input[i] == '"')
			next = handle_double_quote(&head, input, i);
		else
			next = handle_word(&head, input, i);
		if (next < 0)
		{
			free_tokens(head);
			return (NULL);
		}
		i = next;
	}
	return (head);
}
