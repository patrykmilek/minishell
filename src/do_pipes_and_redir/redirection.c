/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:30:20 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/14 11:45:51 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_input_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	handle_output_redirection(const char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirection(t_segment *segment)
{
	t_redir	*redir;

	redir = segment->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_input_redirection(redir->filename);
		else if (redir->type == REDIR_OUT)
			handle_output_redirection(redir->filename,
				O_WRONLY | O_CREAT | O_TRUNC);
		else if (redir->type == APPEND)
			handle_output_redirection(redir->filename,
				O_WRONLY | O_CREAT | O_APPEND);
		else if (redir->type == HEREDOC)
			handle_input_redirection(redir->filename);
		redir = redir->next;
	}
}

void	redirect_io(t_fork_data *data)
{
	if (data->old_input_fd != STDIN_FILENO)
	{
		dup2(data->old_input_fd, STDIN_FILENO);
		close(data->old_input_fd);
	}
	if (!data->is_last)
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
	{
		return (1);
	}
	return (0);
}
