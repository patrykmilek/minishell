/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:19:12 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/04 18:48:57 by pmilek           ###   ########.fr       */
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
	while (*current_token && (*current_token)->type == ARGUMENT)
	{
		segment->args = append_arg(segment->args, (*current_token)->value);
		*current_token = (*current_token)->next;
	}
}

void	process_redirections(t_segment *segment, t_token **current_token)
{
	while (*current_token && ((*current_token)->type == REDIR_IN
			|| (*current_token)->type == REDIR_OUT
			|| (*current_token)->type == APPEND
			|| (*current_token)->type == HEREDOC))
	{
		segment->redir = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (*current_token && (*current_token)->type == ARGUMENT)
		{
			segment->redir_target = ft_strdup((*current_token)->value);
			*current_token = (*current_token)->next;
		}
	}
}

void	process_segment(t_token **current_token,
		t_segment **current_segment, t_segment **head)
{
	t_segment	*new_segment;

	new_segment = init_segment();
	process_command(new_segment, current_token);
	process_arguments(new_segment, current_token);
	process_redirections(new_segment, current_token);
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
	current_token = shell->tokens;
	while (current_token)
	{
		if (current_token->type == PIPE
			&& (!current_token->next || current_token->next->type == PIPE))
		{
			ft_putendl_fd("-bash: syntax error near unexpected token `|'", 2);
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
