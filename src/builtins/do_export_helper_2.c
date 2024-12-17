/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:25 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:26 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_new_node(t_env **new_node, char *key, char *value)
{
	*new_node = malloc(sizeof(t_env));
	if (!*new_node)
		return (ft_putendl_fd("export: malloc error", STDERR_FILENO), 0);
	(*new_node)->next = NULL;
	(*new_node)->key = ft_strdup(key);
	if (!(*new_node)->key)
	{
		free(*new_node);
		return (ft_putendl_fd("export: malloc error for key",
				STDERR_FILENO), 0);
	}
	(*new_node)->value = NULL;
	if (value)
	{
		(*new_node)->value = ft_strdup(value);
		if (!(*new_node)->value)
		{
			free((*new_node)->key);
			free(*new_node);
			return (ft_putendl_fd("export: malloc error for value",
					STDERR_FILENO), 0);
		}
	}
	return (1);
}

void	add_node_to_env(t_shell *shell, t_env *new_node)
{
	t_env	*current;

	if (!shell->env)
	{
		shell->env = new_node;
		return ;
	}
	current = shell->env;
	while (current && current->next)
		current = current->next;
	current->next = new_node;
}

int	update_env_value(t_env *current, char *key, char *value)
{
	if (ft_strcmp(current->key, key) == 0)
	{
		free(current->value);
		current->value = NULL;
		if (value)
		{
			current->value = ft_strdup(value);
			if (!current->value)
				return (ft_putendl_fd("export: malloc error for value",
						STDERR_FILENO), 0);
		}
		return (1);
	}
	return (0);
}

void	add_env_variable(t_shell *shell, char *key, char *value)
{
	if (!add_new_node(shell, key, value))
	{
		ft_putendl_fd("export: failed to add new node", STDERR_FILENO);
		free(key);
		free(value);
	}
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*cleaned;

	if ((str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		|| (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
	{
		len = ft_strlen(str) - 2;
		cleaned = ft_substr(str, 1, len);
		return (cleaned);
	}
	return (ft_strdup(str));
}
