/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:10 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:11 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = NULL;
	return (shell);
}

static void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	free_env(t_env *env)
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;
	t_token	**tokens;

	(void)argc;
	(void)argv;
	init_shell();
	init_env(&shell, envp);
	while (1)
	{
		write(1, "minishell> ", 11);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		trim_newline(input);
		tokens = tokenize_input(input);
		free(input);
		if (!tokens)
		{
			ft_putendl_fd("Error: Tokenization failed", STDERR_FILENO);
			continue ;
		}
		if (execute_commands(&shell, tokens) == 2)
			break ;
		free_tokens(tokens);
	}
	free_env(shell.env);
	return (0);
}
