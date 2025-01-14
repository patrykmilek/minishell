/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:48:25 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/14 11:48:43 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_redir	*create_redirection(t_token_type redir_type, t_token *token)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		perror("malloc failed in create_redirection");
		return (NULL);
	}
	new_redir->type = redir_type;
	new_redir->filename = ft_strdup(token->value);
	if (!new_redir->filename)
	{
		perror("ft_strdup failed in create_redirection");
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}

static void	add_redirection_to_list(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!*redir_list)
		*redir_list = new_redir;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

static int	is_valid_redirection(t_token **current_token)
{
	if (!(*current_token) || (*current_token)->type != ARGUMENT)
	{
		ft_putendl_fd("Syntax error: expected filename after redirection",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	process_redirections(t_segment *segment, t_token **current_token)
{
	t_token_type	redir_type;
	t_redir			*new_redir;

	while (*current_token
		&& ((*current_token)->type == REDIR_IN
			|| (*current_token)->type == REDIR_OUT
			|| (*current_token)->type == APPEND
			|| (*current_token)->type == HEREDOC))
	{
		redir_type = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (!is_valid_redirection(current_token))
			return ;
		new_redir = create_redirection(redir_type, *current_token);
		if (!new_redir)
			return ;
		add_redirection_to_list(&segment->redir_list, new_redir);
		*current_token = (*current_token)->next;
	}
}
