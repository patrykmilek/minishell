/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:39:43 by kubapyciarz       #+#    #+#             */
/*   Updated: 2024/12/17 22:39:44 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(char **args)
{
	int	argscount;

	argscount = 0;
	while (args[argscount])
		argscount++;
	return (argscount);
}

void	trim_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

t_env	*create_oldpwd_node(char *current_pwd)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("cd: malloc error");
		return (NULL);
	}
	new->key = ft_strdup("OLDPWD");
	if (!new->key)
	{
		free(new);
		perror("cd: malloc error");
		return (NULL);
	}
	new->value = ft_strdup(current_pwd);
	if (!new->value)
	{
		free(new->key);
		free(new);
		perror("cd: malloc error");
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_oldpwd_if_missing(t_env *env, char *current_pwd)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
			return ;
		if (!current->next)
			break ;
		current = current->next;
	}
	current->next = create_oldpwd_node(current_pwd);
	if (!current->next)
		perror("cd: failed to add OLDPWD");
}

char	*build_env_entry(t_env *env)
{
	char	*entry;
	char	*temp;

	if (!env->key)
		return (NULL);
	if (env->value)
	{
		temp = ft_strjoin(env->key, "=");
		entry = ft_strjoin(temp, env->value);
		free(temp);
	}
	else
		entry = ft_strdup(env->key);
	return (entry);
}
