#include "minishell.h"
static int handle_input_direction(char *file)
{
        //<
        int fd = open(file, O_RDONLY);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
}
static int handle_output_direction(char *file)
{
        //>
        int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
}
static int handle_append_direction(char *file)
{
        //>>
        int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
                perror(file);
                return (-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
}
static int handle_heredoc_direction(char *file)
{
        //<<
        int fd = handle_heredoc(file);
        if (fd < 0)
        {
                fprintf(stderr, "Error handling heredoc with delimiter: %s\n", delimiter);
                return (-1);
        }
        return fd;
}

void apply_redirections(t_redir *redir)
{
        int fd;
        while (redir)
        {
                if (redir->type == REDIR_IN)
                        handle_input_direction(redir->file);
                else if (redir->type == REDIR_OUT)
                        handle_output_direction(redir->file);
                else if (redir->type == REDIR_APPEND)
                        handle_append_direction(redir->file);
                else if (redir->type == REDIR_HEREDOC)
                {
                        fd = handle_heredoc_direction(redir->file);
                        if (fd < 0)
                                exit(1);
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                }
                redir = redir->next;
        }
}