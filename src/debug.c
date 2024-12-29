/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:00:00 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/29 13:38:48 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const char	*redir_to_string(int redir)
{
	if (redir == REDIR_IN)
		return ("<");
	if (redir == REDIR_OUT)
		return (">");
	if (redir == HEREDOC)
		return ("<<");
	if (redir == APPEND)
		return (">>");
	return ("BRAK_REDIREKCJI");
}

static const char	*relation_to_string(int relation)
{
	if (relation == PIPE)
		return ("PIPE");
	return ("NONE");
}

static void	print_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
	{
		printf("    (brak argumentów)\n");
		return ;
	}
	while (args[i])
	{
		printf("    Arg[%d]: %s\n", i, args[i]);
		i++;
	}
}

void	print_segments(t_segment *segment)
{
	t_segment	*current;
	int			seg_index;

	current = segment;
	seg_index = 0;
	if (!current)
	{
		printf("Brak segmentów do wyświetlenia.\n");
		return ;
	}
	printf("\n============ SEGMENTY ============\n");
	while (current)
	{
		printf("Segment #%d:\n", seg_index++);
		printf("  Command    : %s\n", current->command ? current->command : "(null)");
		printf("  Arguments :\n");
		print_args(current->args);
		printf("  Redirection  : %s\n", redir_to_string(current->redir));
		printf("  Redir Target : %s\n",
			current->redir_target ? current->redir_target : "(null)");
		printf("  Relation   : %s\n", relation_to_string(current->relation));
		printf("----------------------------------\n");
		current = current->next;
	}
	printf("==================================\n\n");
}

static const char	*token_type_to_string(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	if (type == ARGUMENT)
		return ("ARGUMENT");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN (<)");
	if (type == REDIR_OUT)
		return ("REDIR_OUT (>)");
	if (type == APPEND)
		return ("APPEND (>>)");
	if (type == HEREDOC)
		return ("HEREDOC (<<)");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		index;

	current = tokens;
	index = 0;
	if (!tokens)
	{
		printf("No tokens to display.\n");
		return ;
	}
	printf("\n========== TOKENS ==========\n");
	while (current)
	{
		printf("Token %d:\n", index);
		printf("  Type : %s\n", token_type_to_string(current->type));
		printf("  Value: '%s'\n", current->value ? current->value : "(null)");
		printf("----------------------------\n");
		current = current->next;
		index++;
	}
	printf("============================\n");
}
