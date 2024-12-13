/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:22:11 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/06 15:22:25 by jpyciarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (i < dstsize && dst[i] != '\0')
		i++;
	while ((i + j + 1) < dstsize && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	if (dstsize != i)
		dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
