/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_and_free_segments.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:40:32 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/14 11:45:57 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**append_arg(char **args, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc((i + 2) * sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i++] = ft_strdup(arg);
	new_args[i] = NULL;
	free(args);
	return (new_args);
}

static void	free_redirections(t_redir *redir_list)
{
	t_redir	*r;
	t_redir	*r_next;

	r = redir_list;
	while (r)
	{
		r_next = r->next;
		free(r->filename);
		free(r);
		r = r_next;
	}
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_segments(t_segment *segments)
{
	t_segment	*temp_seg;

	while (segments)
	{
		temp_seg = segments;
		segments = segments->next;
		if (temp_seg->command)
			free(temp_seg->command);
		free_args(temp_seg->args);
		free_redirections(temp_seg->redir_list);
		free(temp_seg);
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
	segment->redir_list = NULL;
	segment->relation = NONE;
	segment->next = NULL;
	return (segment);
}
