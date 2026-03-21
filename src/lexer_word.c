#include "minishell.h"

/* Aspas simples: conteúdo literal, sem qualquer expansão.
   'hello $USER' → TOKEN_WORD com valor "hello $USER"          */
int	handle_single_quote(t_token **head, char *input, int i)
{
	int		start;
	char	*value;

	i++;
	start = i;
	while (input[i] && input[i] != '\'')
		i++;
	if (!input[i])
		return (syntax_error("aspas simples nao fechadas", '\''));
	value = ft_substr(input, start, i - start);
	if (!value)
		return (-1);
	token_list_add(head, new_token(TOKEN_WORD, value));
	free(value);
	return (i + 1);
}

/* Aspas duplas: conteúdo preservado para expansão na Fase 4.
   "hello $USER" → TOKEN_WORD com valor "hello $USER" (literal por agora) */
int	handle_double_quote(t_token **head, char *input, int i)
{
	int		start;
	char	*value;

	i++;
	start = i;
	while (input[i] && input[i] != '"')
		i++;
	if (!input[i])
		return (syntax_error("aspas duplas nao fechadas", '"'));
	value = ft_substr(input, start, i - start);
	if (!value)
		return (-1);
	token_list_add(head, new_token(TOKEN_WORD, value));
	free(value);
	return (i + 1);
}

/* Palavra normal: acumula chars até espaço, operador ou aspas.
   Suporta mistura: echo he"llo" → um único TOKEN_WORD "hello"  */
int	handle_word(t_token **head, char *input, int i)
{
	int		start;
	char	*seg;
	char	*val;
	char	*tmp;
	t_token	*sub;

	val = ft_strdup("");
	if (!val)
		return (-1);
	while (input[i] && input[i] != ' ' && input[i] != '\t'
		&& !is_operator(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			sub = NULL;
			if (input[i] == '\'')
				i = handle_single_quote(&sub, input, i);
			else
				i = handle_double_quote(&sub, input, i);
			if (i < 0 || !sub)
			{
				free(val);
				return (-1);
			}
			tmp = ft_strjoin(val, sub->value);
			free(val);
			free_tokens(sub);
			if (!tmp)
				return (-1);
			val = tmp;
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\t'
				&& !is_operator(input[i])
				&& input[i] != '\'' && input[i] != '"')
				i++;
			seg = ft_substr(input, start, i - start);
			if (!seg)
			{
				free(val);
				return (-1);
			}
			tmp = ft_strjoin(val, seg);
			free(val);
			free(seg);
			if (!tmp)
				return (-1);
			val = tmp;
		}
	}
	token_list_add(head, new_token(TOKEN_WORD, val));
	free(val);
	return (i);
}
