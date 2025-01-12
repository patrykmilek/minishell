/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:10 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 13:01:58 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_shell	*init_shell(int shell_layer)
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

static void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env(shell->env);
	free_tokens(shell->tokens);
	free_segments(shell->segment);
	free(shell);
}

static char	*generate_layered_prompt(int shell_layer)
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

char	*generate_prompt(int shell_layer)
{
	char	*prompt;

	if (shell_layer == 0)
	{
		prompt = ft_strjoin("minishell", "> ");
		if (!prompt)
			return (NULL);
	}
	else
	{
		prompt = generate_layered_prompt(shell_layer);
		if (!prompt)
			return (NULL);
	}
	return (prompt);
}

static int	initialize_shell(int argc, char **argv,
	t_shell **shell, char **envp)
{
	int	shell_layer;

	if (argc > 1 && argv[1])
		shell_layer = ft_atoi(argv[1]);
	else
		shell_layer = 0;
	*shell = init_shell(shell_layer);
	if (!*shell)
	{
		perror("Failed to initialize shell");
		return (EXIT_FAILURE);
	}
	init_env(*shell, envp);
	setup_signals();
	return (0);
}

static char	*get_user_input(t_shell *shell)
{
	char	*prompt;
	char	*input;

	prompt = generate_prompt(shell->shell_layer);
	input = readline(prompt);
	free(prompt);
	return (input);
}

static int	handle_user_input(t_shell *shell, char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	if (*input)
		add_history(input);
	trim_newline(input);
	shell->tokens = tokenize_input(input);
	free(input);
	if (!shell->tokens)
		return (0);
	return (execute_commands(shell, shell->tokens));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	int		exit_status;

	if (initialize_shell(argc, argv, &shell, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		input = get_user_input(shell);
		exit_status = handle_user_input(shell, input);
		if (exit_status == 1 || exit_status == 2)
			break ;
	}
	cleanup_shell(shell);
	return (0);
}
