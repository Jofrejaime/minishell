#include "minishell.h"

/* Retorna 1 se o char é um operador de shell */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* Trata <  e  <<
   Verifica sempre o char seguinte antes de classificar.        */
static int	handle_redir_in(t_token **head, char *input, int i)
{
	if (input[i + 1] == '<')
	{
		token_list_add(head, new_token(TOKEN_HEREDOC, "<<"));
		return (i + 2);
	}
	token_list_add(head, new_token(TOKEN_REDIR_IN, "<"));
	return (i + 1);
}

/* Trata >  e  >>  */
static int	handle_redir_out(t_token **head, char *input, int i)
{
	if (input[i + 1] == '>')
	{
		token_list_add(head, new_token(TOKEN_APPEND, ">>"));
		return (i + 2);
	}
	token_list_add(head, new_token(TOKEN_REDIR_OUT, ">"));
	return (i + 1);
}

/* Ponto de entrada — delega por tipo de operador.
   || é erro de sintaxe (não suportado no minishell base).      */
int	handle_operator(t_token **head, char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (syntax_error("operador inesperado", '|'));
		token_list_add(head, new_token(TOKEN_PIPE, "|"));
		return (i + 1);
	}
	if (input[i] == '<')
		return (handle_redir_in(head, input, i));
	return (handle_redir_out(head, input, i));
}
