/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                                              */
/*   includes/minishell.h                                                     */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ------------------------------------------------------------------ */
/*  Variável global — única permitida pela norma 42                    */
/* ------------------------------------------------------------------ */

extern int	g_exit_status;

/* ------------------------------------------------------------------ */
/*  Tipos de token                                                      */
/* ------------------------------------------------------------------ */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

/* ------------------------------------------------------------------ */
/*  Lista ligada de tokens (Fase 2)                                    */
/* ------------------------------------------------------------------ */

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* ------------------------------------------------------------------ */
/*  Estrutura de comando (Fase 3 — stub por agora)                     */
/* ------------------------------------------------------------------ */

typedef struct s_cmd
{
	char			**args;
	t_token_type	redir_type;
	char			*redir_file;
	struct s_cmd	*next;
}	t_cmd;

/* ------------------------------------------------------------------ */
/*  Struct principal do shell                                           */
/* ------------------------------------------------------------------ */

typedef struct s_shell
{
	char	**env;
	char	*input;
	int		exit_status;
}	t_shell;

/* ------------------------------------------------------------------ */
/*  inits.c                                                             */
/* ------------------------------------------------------------------ */

int		init_shell(t_shell *shell, char **envp);
char	**init_env(char **envp);
char	*ft_getenv(char **env, const char *name);

/* ------------------------------------------------------------------ */
/*  free.c                                                              */
/* ------------------------------------------------------------------ */

void	handle_eof(t_shell *shell);
void	free_shell(t_shell *shell);
void	free_env(char **env);

/* ------------------------------------------------------------------ */
/*  read_input.c                                                        */
/* ------------------------------------------------------------------ */

char	*build_prompt(t_shell *shell);
int		is_empty(const char *str);
void	process_input(t_shell *shell, char *input);

/* ------------------------------------------------------------------ */
/*  sinais.c                                                            */
/* ------------------------------------------------------------------ */

void	setup_signals_prompt(void);
void	setup_signals_child(void);
void	handle_sigint(int sig);

/* ------------------------------------------------------------------ */
/*  lexer.c                                                             */
/* ------------------------------------------------------------------ */

t_token	*lexer(char *input);
t_token	*new_token(t_token_type type, char *value);
void	token_list_add(t_token **head, t_token *new);
void	free_tokens(t_token *head);

/* ------------------------------------------------------------------ */
/*  lexer_word.c                                                        */
/* ------------------------------------------------------------------ */

int		handle_word(t_token **head, char *input, int i);
int		handle_single_quote(t_token **head, char *input, int i);
int		handle_double_quote(t_token **head, char *input, int i);

/* ------------------------------------------------------------------ */
/*  lexer_operator.c                                                    */
/* ------------------------------------------------------------------ */

int		handle_operator(t_token **head, char *input, int i);
int		is_operator(char c);

/* ------------------------------------------------------------------ */
/*  lexer_utils.c                                                       */
/* ------------------------------------------------------------------ */

int		skip_spaces(char *input, int i);
int		syntax_error(char *context, char c);
void	print_tokens(t_token *head);
char	*token_type_str(t_token_type type);

/* ------------------------------------------------------------------ */
/*  parser.c                                                           */
/* ------------------------------------------------------------------ */

t_cmd	*parser(t_token *tokens);
void	free_cmds(t_cmd *cmds);

/*---------------------------------------------------------------------- */
/*  Funções da libft usadas                                             */
/* ------------------------------------------------------------------- */

void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	run_shell(t_shell *shell);
# endif
