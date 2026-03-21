#include "minishell.h"

void    setup_signals_prompt(void)
{
    struct sigaction    sa;

    sa.sa_flags = SA_RESTART;      /* evita EINTR em chamadas bloqueantes */
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);  /* Ctrl+C → handler próprio */
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL); /* Ctrl+\ → ignorado no prompt */
}

void    handle_sigint(int sig)
{
    (void)sig;
    g_exit_status = 130;       /* padrão bash: 128 + número do sinal */
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();          /* informa readline que mudou de linha */
    rl_replace_line("", 0);    /* limpa o buffer de edição */
    rl_redisplay();            /* redesenha o prompt em branco */
}

void    setup_signals_child(void)
{
    signal(SIGINT,  SIG_DFL);  /* filho recebe e morre com SIGINT */
    signal(SIGQUIT, SIG_DFL);  /* filho recebe e morre com SIGQUIT */
}
