/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:50 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:18:57 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit"))
		return (2);
	return (0);
}

static void	free_args(char **args)
{
	int	i;

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

int	check_for_pipes(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (current->type == PIPE || current->type == REDIR_IN
			|| current->type == REDIR_OUT || current->type == APPEND
			|| current->type == HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

int	execute_commands(t_shell *shell, t_token **tokens)
{
	t_token	*tmp_token;

	(void)tokens;
	parse_tokens(shell);
	if (ft_strcmp(shell->segment->command, "exit") == 0)
		return (2);
	tmp_token = malloc(sizeof(t_token));
	if (!tmp_token)
		return (1);
	if (!shell->segment->relation && is_parent_builtin(shell->segment->command))
	{
		tmp_token->type = COMMAND;
		tmp_token->value = shell->segment->command;
		tmp_token->next = NULL;
		do_builtins(shell, tmp_token, shell->segment->args);
	}
	else
		execute_segments(shell);
	free(tmp_token);
	return (0);
}
