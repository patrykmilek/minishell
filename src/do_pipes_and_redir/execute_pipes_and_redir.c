/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_and_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:45:54 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/15 18:10:51 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_fork_data *data)
{
	t_token	tmp_token;
	int		ret;

	redirect_io(data);
	handle_redirection(data->current);
	if (is_builtin_command(data->current->command) == 1)
	{
		tmp_token.type = COMMAND;
		tmp_token.value = data->current->command;
		tmp_token.next = NULL;
		ret = do_builtins(data->shell, &tmp_token, data->current->args);
		exit(ret);
	}
	else if (!do_executable(data->shell, data->current->command,
			data->current->args))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->current->command, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	exit(EXIT_SUCCESS);
}

static int	setup_fork(t_fork_data *data)
{
	pid_t	pid;

	if (!data->is_last && pipe(data->pipe_fd) == -1)
		return (perror("pipe failed"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid == 0)
		child_process(data);
	if (data->old_input_fd != STDIN_FILENO)
		close(data->old_input_fd);
	if (!data->is_last)
	{
		close(data->pipe_fd[1]);
		data->old_input_fd = data->pipe_fd[0];
	}
	return (pid);
}

static int	count_segments(t_segment *seg)
{
	int	count;

	count = 0;
	while (seg)
	{
		count++;
		seg = seg->next;
	}
	return (count);
}

static pid_t	*init_fork(t_shell *shell, int segment_count)
{
	t_fork_data	data;
	pid_t		*child_pids;
	int			i;

	child_pids = malloc(sizeof(pid_t) * segment_count);
	if (!child_pids)
		return (perror("malloc failed"), NULL);
	data.shell = shell;
	data.old_input_fd = STDIN_FILENO;
	data.current = shell->segment;
	i = 0;
	while (data.current)
	{
		data.is_last = (data.current->relation != PIPE);
		child_pids[i] = setup_fork(&data);
		if (child_pids[i++] == EXIT_FAILURE)
		{
			free(child_pids);
			return (NULL);
		}
		data.current = data.current->next;
	}
	return (child_pids);
}

int	execute_segments(t_shell *shell)
{
	int		segment_count;
	pid_t	*child_pids;
	int		i;

	segment_count = count_segments(shell->segment);
	if (segment_count == 0)
		return (0);
	child_pids = init_fork(shell, segment_count);
	if (!child_pids)
	{
		free_segments(shell->segment);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < segment_count)
		waitpid(child_pids[i++], NULL, 0);
	free(child_pids);
	return (0);
}
