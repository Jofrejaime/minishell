#include "minishell.h"

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
