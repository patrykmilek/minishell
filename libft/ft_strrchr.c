/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:09:16 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/12 12:52:21 by jpyciarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char const	*temp;
	int			i;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			temp = &s[i];
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	else
		return ((char *)temp);
}
