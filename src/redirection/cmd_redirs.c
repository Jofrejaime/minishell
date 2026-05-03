#include "minishell.h"

typedef struct s_cmd_redirs
{
    t_cmd *cmd;
    t_redir *redirs;
    struct s_cmd_redirs *next;
}   t_cmd_redirs;

static t_cmd_redirs *g_cmd_redirs = NULL;

static t_redir *copy_redir_node(t_redir *r)
{
    t_redir *n;

    n = malloc(sizeof(t_redir));
    if (!n)
        return (NULL);
    n->type = r->type;
    n->file = ft_strdup(r->file);
    n->next = NULL;
    return (n);
}

void add_redir_for_cmd(t_cmd *cmd, t_redir *redir)
{
    t_cmd_redirs *it = g_cmd_redirs;
    t_cmd_redirs *prev = NULL;
    t_redir *copy;

    if (!redir || !cmd)
        return ;
    copy = copy_redir_node(redir);
    if (!copy)
        return ;
    while (it)
    {
        if (it->cmd == cmd)
        {
            copy->next = it->redirs;
            it->redirs = copy;
            return ;
        }
        prev = it;
        it = it->next;
    }
    it = malloc(sizeof(t_cmd_redirs));
    if (!it)
    {
        free(copy->file);
        free(copy);
        return ;
    }
    it->cmd = cmd;
    it->redirs = copy;
    it->next = NULL;
    if (prev)
        prev->next = it;
    else
        g_cmd_redirs = it;
}

t_redir *get_redirs_for_cmd(t_cmd *cmd)
{
    t_cmd_redirs *it = g_cmd_redirs;

    while (it)
    {
        if (it->cmd == cmd)
            return (it->redirs);
        it = it->next;
    }
    return (NULL);
}

static void free_redir_list(t_redir *r)
{
    t_redir *tmp;
    while (r)
    {
        tmp = r->next;
        free(r->file);
        free(r);
        r = tmp;
    }
}

void clear_cmd_redirs(void)
{
    t_cmd_redirs *it = g_cmd_redirs;
    t_cmd_redirs *tmp;

    while (it)
    {
        tmp = it->next;
        free_redir_list(it->redirs);
        free(it);
        it = tmp;
    }
    g_cmd_redirs = NULL;
}
