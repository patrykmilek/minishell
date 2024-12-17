/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:27 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:28 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_size(t_env *env)
{
	int	size;

	if (!env)
		return (0);
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static char	**env_to_tab(t_env *env)
{
	char	**tab;
	int		i;

	if (!env)
	{
		tab = malloc(sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = build_env_entry(env);
		if (tab != NULL)
			i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

static void	sort_tab(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_env(t_shell *shell)
{
	char	**tab;

	tab = env_to_tab(shell->env);
	if (!tab)
	{
		perror("export: malloc error");
		return (NULL);
	}
	sort_tab(tab);
	return (tab);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(tab[i], STDOUT_FILENO);
		free(tab[i]);
		i++;
	}
	free(tab);
}
