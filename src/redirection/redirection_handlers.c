#include "minishell.h"

static int handle_input_direction(char *file)
{
        //<
        int     fd;

        fd = open(file, O_RDONLY);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
                perror("dup2");
                close(fd);
                return (-1);
        }
        if(close(fd) < 0)
        {
                perror("close");
                return (-1);
        }
        return (0);
}
static int handle_output_direction(char *file)
{
        //>
        int     fd;
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
                perror("dup2");
                close(fd);
                return (-1);
        }
        if(close(fd) < 0)
        {
                perror("close");
                return (-1);
        }
        return (0);
}
static int handle_append_direction(char *file)
{
        //>>
        int     fd;

        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
                perror("dup2");
                close(fd);
                return (-1);
        }
        if(close(fd) < 0)
        {
                perror("close");
                return (-1);
        }
        return (0);
}
static int handle_heredoc_direction(char *delimiter)
{
        //<<
        int     fd;

        fd = handle_heredoc(delimiter);
        if (fd < 0)
        {
                fprintf(stderr, "Error handling heredoc with delimiter: %s\n", delimiter);
                return (-1);
        }
        if(dup2(fd, STDIN_FILENO) < 0)
        {
                perror("dup2");
                close(fd);
                return (-1);
        }
        if (close(fd) < 0)
        {
                perror("close");
                return (-1);
        }
        return (0);
}

int apply_redirections(t_redir *redir, int prev_fd)
{
        while (redir)
        {
                if (prev_fd != -1 && (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC))
                {
                        /* skip input redirections when input comes from previous pipe */
                        redir = redir->next;
                        continue;
                }
                if (redir->type == REDIR_IN && handle_input_direction(redir->file) < 0)
                        return (-1);
                else if (redir->type == REDIR_OUT && handle_output_direction(redir->file) < 0)
                        return (-1);
                else if (redir->type == REDIR_APPEND && handle_append_direction(redir->file) < 0)
                        return (-1);
                else if (redir->type == REDIR_HEREDOC && (handle_heredoc_direction(redir->file)) < 0)
                        return (-1);
                redir = redir->next;
        }
        return (0);
}