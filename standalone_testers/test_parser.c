/*
copia e cola o comando abaixo para compilar e testar o parser: 
 
gcc -Wall -Wextra -I ../includes -o test_parser \
    test_parser.c \
    ../src/parser/parser.c \
    ../src/parser/parser_utils.c \
    ../src/parser/parser_cmds.c \
    ../src/lexer/lexer.c \
    ../src/lexer/lexer_word.c \
    ../src/lexer/lexer_operator.c \
    ../src/lexer/lexer_utils.c \
    ../mini_libft/libft.a
    
    */

#include "minishell.h"
 
int	g_exit_status;
 
static void	print_cmds(t_cmd *c)
{
	int	n = 1;
	while (c)
	{
		printf("[cmd %d] args:", n++);
		for (int i = 0; c->args && c->args[i]; i++)
			printf(" \"%s\"", c->args[i]);
		if (c->redir_file)
			printf(" | redir: %d \"%s\"", c->redir_type, c->redir_file);
		printf("\n");
		c = c->next;
	}
}
 
int	main(int argc, char **argv)
{
	t_token	*toks;
	t_cmd	*cmds;
	int		i;
 
	if (argc < 2)
	{
		printf("uso: ./test_parser \"comando\"\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		printf("\n>> \"%s\"\n", argv[i]);
		toks = lexer(argv[i]);
		if (!toks)
		{
			printf("   (lexer retornou NULL)\n");
			i++;
			continue ;
		}
		print_tokens(toks);
		cmds = parser(toks);
		if (cmds)
			print_cmds(cmds);
		else
			printf("   (parser retornou NULL)\n");
		free_cmds(cmds);
		free_tokens(toks);
		i++;
	}
	return (0);
}