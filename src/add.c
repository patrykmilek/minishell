/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:59 by pmilek            #+#    #+#             */
/*   Updated: 2025/01/15 17:55:53 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

t_shell	*init_shell(int shell_layer)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = NULL;
	shell->tokens = NULL;
	shell->segment = NULL;
	shell->is_child = 0;
	shell->pid = -1;
	shell->shell_layer = shell_layer;
	return (shell);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env(shell->env);
	free_tokens(shell->tokens);
	free_segments(shell->segment);
	rl_clear_history();
	free(shell);
}

char	*generate_layered_prompt(int shell_layer)
{
	char	*layer_str;
	char	*temp1;
	char	*temp2;
	char	*prompt;

	layer_str = ft_itoa(shell_layer);
	if (!layer_str)
		return (NULL);
	temp1 = ft_strjoin("minishell[", layer_str);
	free(layer_str);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, "]> ");
	free(temp1);
	if (!temp2)
		return (NULL);
	prompt = temp2;
	return (prompt);
}
