/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:29 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:30 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_forbidden_sign(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_new_node(t_shell *shell, char *key, char *value)
{
	t_env	*new_node;

	if (!init_new_node(&new_node, key, value))
		return (0);
	add_node_to_env(shell, new_node);
	return (1);
}

static void	extract_key_and_value(char *str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		*key = ft_substr(str, 0, equal_sign - str);
		*value = remove_quotes(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(str);
		*value = NULL;
	}
}

void	update_or_add_env(t_shell *shell, char *str)
{
	t_env	*current;
	char	*key;
	char	*value;

	extract_key_and_value(str, &key, &value);
	if (!key || !check_key(key))
	{
		ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
		free(key);
		free(value);
		return ;
	}
	current = shell->env;
	while (current)
	{
		if (update_env_value(current, key, value))
		{
			free(key);
			free(value);
			return ;
		}
		current = current->next;
	}
	add_env_variable(shell, key, value);
}

int	do_export(t_shell *shell, char **args)
{
	char	**tab;
	int		i;

	if (args[0] == NULL)
	{
		tab = sort_env(shell);
		if (!tab)
			return (1);
		print_tab(tab);
		return (1);
	}
	i = 0;
	while (args[i])
	{
		if (!check_forbidden_sign(args[i]))
		{
			ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
			ft_putendl_fd(args[i], STDERR_FILENO);
		}
		else
			update_or_add_env(shell, args[i]);
		i++;
	}
	return (1);
}
