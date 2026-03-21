#include "minishell.h"

int	g_exit_status = 0;

#ifdef DEBUG_LEXER
static void	debug_lexer(char *input)
{
	t_token	*tokens;
	t_token	*tmp;
	int		count;

	count = 0;
	printf("\n--- lexer(\"%s\") ---\n", input);
	tokens = lexer(input);
	if (!tokens)
	{
		printf("  resultado: NULL (erro de sintaxe)\n---\n\n");
		return ;
	}
	tmp = tokens;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	printf("  %d token%s:\n", count, count != 1 ? "s" : "");
	print_tokens(tokens);
	printf("---\n\n");
	free_tokens(tokens);
}
#endif

void	run_shell(t_shell *shell)
{
	char	*prompt;
	char	*input;

	while (1)
	{
		setup_signals_prompt();
		prompt = build_prompt(shell);
		input = readline(prompt);
		free(prompt);
		if (!input)
			handle_eof(shell);
		if (!is_empty(input))
		{
			add_history(input);
#ifdef DEBUG_LEXER
			debug_lexer(input);
#else
			process_input(shell, input);
#endif
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp) != 0)
		return (1);
#ifdef DEBUG_LEXER
	printf("=== MINISHELL — MODO DEBUG LEXER ===\n");
	printf("    Escreve comandos para ver os tokens.\n");
	printf("    Ctrl+D para sair.\n\n");
#endif
	run_shell(&shell);
	free_shell(&shell);
	return (g_exit_status);
}
