/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:11:15 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/12 12:27:55 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	max_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		max_len = s_len - start;
	else
		max_len = len;
	new_str = (char *)malloc(max_len + 1);
	if (!new_str)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < max_len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}
