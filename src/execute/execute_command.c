/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:50 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/04 19:53:26 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit"))
		return (2);
	return (0);
}

static void	free_args(char **args)
{
	int		i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	do_command(t_shell *shell, t_token *current_token)
{
	char	**args;

	args = create_arg_list(current_token->next);
	if (is_builtin_command(current_token->value) == 1)
	{
		if (!args)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
			return (2);
		}
		if (do_builtins(shell, current_token, args) == 0)
		{
			ft_putendl_fd("blad", STDERR_FILENO);
			return (1);
		}
	}
	free_args(args);
	return (0);
}

static void	execute_parent_builtin(t_shell *shell)
{
	t_token	tmp_token;

	tmp_token.type = COMMAND;
	tmp_token.value = shell->segment->command;
	tmp_token.next = NULL;
	do_builtins(shell, &tmp_token, shell->segment->args);
}

int	execute_commands(t_shell *shell, t_token **tokens)
{
	(void)tokens;
	parse_tokens(shell);
	if (!shell->segment || !shell->segment->command)
	{
		ft_putendl_fd("-bash: command not found", STDERR_FILENO);
		return (0);
	}
	if (ft_strcmp(shell->segment->command, "exit") == 0)
		return (2);
	if (!shell->segment->relation && is_parent_builtin(shell->segment->command))
		execute_parent_builtin(shell);
	else
		execute_segments(shell);
	free_segments(shell->segment);
	shell->segment = NULL;
	return (0);
}
