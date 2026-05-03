#include "minishell.h"

int	redirection(t_cmd *cmd, int prev_fd)
{
    t_redir *list;

    if (!cmd)
        return (0);
    list = get_redirs_for_cmd(cmd);
    if (!list)
        return (0);
    return (apply_redirections(list, prev_fd));
}