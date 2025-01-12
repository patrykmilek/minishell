/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:31:12 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 12:46:55 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(const char *error_msg, t_shell *shell)
{
	if (error_msg)
		perror(error_msg);
	if (shell->pid > 0 && shell->is_child == 0)
	{
		kill(shell->pid, SIGKILL);
		waitpid(shell->pid, NULL, 0);
	}
	if (shell)
	{
		free_tokens(shell->tokens);
		free_segments(shell->segment);
		free_env(shell->env);
	}
	do_executable(shell, NULL, NULL);
}
