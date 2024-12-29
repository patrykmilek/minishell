/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:30:20 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:32:41 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**append_arg(char **args, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc((i + 2) * sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i++] = ft_strdup(arg);
	new_args[i] = NULL;
	free(args);
	return (new_args);
}

static int	open_redirection_file(t_segment *segment)
{
	int	redir_fd;

	if (segment->redir == REDIR_OUT)
		redir_fd = open(segment->redir_target, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (segment->redir == APPEND)
		redir_fd = open(segment->redir_target, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else if (segment->redir == REDIR_IN)
		redir_fd = open(segment->redir_target, O_RDONLY);
	else
		return (-1);
	if (redir_fd == -1)
	{
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	return (redir_fd);
}

void	handle_redirection(t_segment *segment)
{
	int	redir_fd;

	if (segment->redir == NONE)
		return ;
	redir_fd = open_redirection_file(segment);
	if (redir_fd < 0)
		return ;
	if (segment->redir == REDIR_OUT || segment->redir == APPEND)
		dup2(redir_fd, STDOUT_FILENO);
	else if (segment->redir == REDIR_IN)
		dup2(redir_fd, STDIN_FILENO);
	close(redir_fd);
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
