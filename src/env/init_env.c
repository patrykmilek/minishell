/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:45 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:46 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env(t_shell *shell, char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		enviter;
	char	*delimiter;

	head = NULL;
	current = NULL;
	enviter = 0;
	while (env[enviter])
	{
		new_node = malloc(sizeof(t_env));
		delimiter = ft_strchr(env[enviter], '=');
		new_node->key = ft_substr(env[enviter], 0, delimiter - env[enviter]);
		new_node->value = ft_strdup(delimiter + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		enviter++;
	}
	shell->env = head;
}
