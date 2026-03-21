#include "minishell.h"

/* Avança i sobre espaços e tabs. Retorna novo índice. */
int	skip_spaces(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (i);
}

/* Imprime erro de sintaxe estilo bash e retorna -1.
   O -1 é propagado até lexer() que liberta a lista e retorna NULL. */
int	syntax_error(char *context, char c)
{
	write(STDERR_FILENO, "minishell: syntax error: ", 25);
	write(STDERR_FILENO, context, ft_strlen(context));
	write(STDERR_FILENO, " `", 2);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "'\n", 2);
	g_exit_status = 2;
	return (-1);
}

/* Converte tipo de token em string — só para debug/print_tokens */
char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD      ");
	if (type == TOKEN_PIPE)
		return ("PIPE      ");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN  ");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT ");
	if (type == TOKEN_APPEND)
		return ("APPEND    ");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC   ");
	return ("UNKNOWN   ");
}

/* Imprime lista de tokens no formato:
     [0] WORD       -> "echo"
     [1] PIPE       -> "|"
   Chamada pelo modo DEBUG_LEXER em run_shell.c                  */
void	print_tokens(t_token *head)
{
	int	i;

	i = 0;
	if (!head)
	{
		write(STDOUT_FILENO, "  (NULL — erro de sintaxe)\n", 27);
		return ;
	}
	while (head)
	{
		printf("  [%d] %s -> \"%s\"\n", i,
			token_type_str(head->type), head->value);
		i++;
		head = head->next;
	}
}
