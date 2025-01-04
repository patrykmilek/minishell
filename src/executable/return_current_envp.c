/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_current_envp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:36:18 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/04 19:37:11 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**allocate_envp(t_env *env, int count)
{
	char	**envp;
	char	*entry;
	int		i;

	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		entry = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(entry, env->value);
		free(entry);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**get_envp(t_shell *shell)
{
	int		count;

	count = count_env_vars(shell->env);
	return (allocate_envp(shell->env, count));
}
