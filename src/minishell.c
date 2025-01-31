/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:10 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 17:14:11 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*generate_prompt(int shell_layer)
{
	static char	*previous_prompt = NULL;
	char		*layer_str;
	char		*temp1;
	char		*temp2;

	if (previous_prompt)
		free(previous_prompt);
	if (shell_layer == 0)
		return (previous_prompt = ft_strdup("minishell> "));
	layer_str = ft_itoa(shell_layer);
	if (!layer_str)
		return (NULL);
	temp1 = ft_strjoin("minishell[", layer_str);
	free(layer_str);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, "]> ");
	free(temp1);
	return (previous_prompt = temp2);
}

static int	initialize_shell(int argc, char **argv,
			t_shell **shell, char **envp)
{
	int	shell_layer;

	shell_layer = 0;
	if (argc > 1 && argv[1])
		shell_layer = ft_atoi(argv[1]);
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
	char	*input;
	char	*line;
	char	*temp_prompt;
	char	*temp;

	input = readline(generate_prompt(shell->shell_layer));
	while (input && has_unclosed_quotes(input))
	{
		temp_prompt = ft_strdup("> ");
		line = readline(temp_prompt);
		free(temp_prompt);
		if (!line)
		{
			free(input);
			return (NULL);
		}
		temp = input;
		input = ft_strjoin(input, "\n");
		free(temp);
		temp = input;
		input = ft_strjoin(input, line);
		free(temp);
		free(line);
	}
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
