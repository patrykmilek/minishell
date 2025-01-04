/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:10 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/04 20:12:11 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = NULL;
	shell->tokens = NULL;
	shell->is_child = 0;
	shell->pid = -1;
	return (shell);
}

void free_tokens(t_token **tokens)
{
    int i = 0;

    if (!tokens)
        return;

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

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_shell *shell;
    t_token **tokens = NULL;

    (void)argc;
    (void)argv;
    shell = init_shell();
    if (!shell)
    {
        perror("Failed to initialize shell");
        return (1);
    }

    init_env(shell, envp);
    setup_signals();

    while (1)
{
    input = readline("minishell> ");
    if (!input)
    {
        write(1, "exit\n", 5);
        break;
    }

    while (has_unclosed_quotes(input))
    {
        char *continuation = readline("> ");
        if (!continuation)
        {
            ft_putendl_fd("minishell: unexpected EOF while looking for matching quote", STDERR_FILENO);
            free(input);
            break;
        }

        char *tmp = ft_strjoin(input, "\n");
        free(input);
        input = ft_strjoin(tmp, continuation);
        free(tmp);
        free(continuation);
    }

    if (!input)
        continue;

    if (*input)
        add_history(input);

    trim_newline(input);
    tokens = tokenize_input(input);

    free(input);

    if (!tokens)
        continue;

    shell->tokens = *tokens;

    if (execute_commands(shell, tokens) == 2)
        break;

    free_tokens(tokens);
    tokens = NULL;

    free_segments(shell->segment);
    shell->segment = NULL;
}

    if (tokens)
        free_tokens(tokens);
    if (shell->segment)
        free_segments(shell->segment);

    free_env(shell->env);
    free(shell);
    return (0);
}

