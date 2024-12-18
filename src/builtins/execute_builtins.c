/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:39 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/18 14:51:25 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_builtins(t_shell *shell, t_token *current_token, char **args)
{
	int	is_done;

	is_done = 0;
	if (ft_strncmp(current_token->value, "echo",
			4) == 0 && current_token->value[4] == '\0')
		is_done = do_echo(shell, args);
	else if (ft_strncmp(current_token->value,
			"pwd", 3) == 0 && current_token->value[3] == '\0')
		is_done = do_pwd();
	else if (ft_strncmp(current_token->value,
			"env", 3) == 0 && current_token->value[3] == '\0')
		is_done = do_env(shell);
	else if (ft_strncmp(current_token->value,
			"cd", 2) == 0 && current_token->value[2] == '\0')
		is_done = do_cd(shell, args);
	else if (ft_strncmp(current_token->value,
			"export", 6) == 0 && current_token->value[6] == '\0')
		is_done = do_export(shell, args);
	else if (ft_strncmp(current_token->value,
			"unset", 5) == 0 && current_token->value[5] == '\0')
		is_done = do_unset(shell, args);
	return (is_done);
}
