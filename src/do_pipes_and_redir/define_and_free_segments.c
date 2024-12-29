/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_and_free_segments.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:26:57 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/28 19:22:36 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_segments(t_segment *segments)
{
	t_segment	*temp;
	int			i;

	while (segments)
	{
		temp = segments;
		segments = segments->next;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->redir_target)
			free(temp->redir_target);
		free(temp);
	}
}

t_segment	*init_segment(void)
{
	t_segment	*segment;

	segment = malloc(sizeof(t_segment));
	if (!segment)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	segment->command = NULL;
	segment->args = NULL;
	segment->redir = NONE;
	segment->redir_target = NULL;
	segment->relation = NONE;
	segment->next = NULL;
	return (segment);
}
