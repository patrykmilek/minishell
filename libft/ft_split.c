/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:31:50 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/12 12:48:56 by jpyciarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*word_add(const char *str, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i++] = str[start++];
	}
	result[i] = '\0';
	return (result);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free (strs);
	return (NULL);
}

static void	ft_declaration(size_t *i, int *j, int *word_trigger)
{
	*i = 0;
	*j = 0;
	*word_trigger = -1;
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		word_trigger;

	ft_declaration(&i, &j, &word_trigger);
	result = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && word_trigger < 0)
			word_trigger = i;
		else if ((s[i] == c || i == ft_strlen(s)) && word_trigger >= 0)
		{
			result[j] = word_add(s, word_trigger, i);
			if (!result[j])
				return (ft_free(result, j));
			word_trigger = -1;
			j++;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}
