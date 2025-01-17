/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:19:12 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/17 20:31:55 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_command(t_segment *segment, t_token **current_token)
{
	if ((*current_token)->type == COMMAND)
	{
		if (segment->command)
			free(segment->command);
		segment->command = ft_strdup((*current_token)->value);
		*current_token = (*current_token)->next;
	}
}

void	process_arguments(t_segment *segment, t_token **current_token)
{
	char	**temp;

	while (*current_token && (*current_token)->type == ARGUMENT)
	{
		temp = segment->args;
		segment->args = append_arg(segment->args, (*current_token)->value);
		if (!segment->args)
		{
			free_args(temp);
			return ;
		}
		*current_token = (*current_token)->next;
	}
}

void	process_segment(t_token **current_token,
		t_segment **current_segment, t_segment **head)
{
	t_segment	*new_segment;

	new_segment = init_segment();
	if (!new_segment)
		return ;
	process_command(new_segment, current_token);
	process_arguments(new_segment, current_token);
	process_redirections(new_segment, current_token);
	if (!new_segment->command && !new_segment->args && !new_segment->redir_list)
	{
		free_segments(new_segment);
		return ;
	}
	if (!(*head))
		*head = new_segment;
	else
		(*current_segment)->next = new_segment;
	*current_segment = new_segment;
}

void	parse_tokens(t_shell *shell)
{
	t_token		*current_token;
	t_segment	*head;
	t_segment	*current_segment;

	head = NULL;
	current_segment = NULL;
	current_token = *shell->tokens;
	while (current_token)
	{
		if (current_token->type == PIPE
			&& (!current_token->next || current_token->next->type == PIPE))
		{
			ft_putendl_fd("ms: error near unexpected token `|'", STDERR_FILENO);
			free_segments(head);
			shell->segment = NULL;
			return ;
		}
		process_segment(&current_token, &current_segment, &head);
		if (current_token && current_token->type == PIPE)
		{
			current_segment->relation = PIPE;
			current_token = current_token->next;
		}
	}
	shell->segment = head;
}
