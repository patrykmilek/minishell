/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:36:37 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/22 13:03:16 by jpyciarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*allocated_mem;
	size_t			total_size;

	if (nmemb <= 0 || size <= 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (2147483647 / nmemb < size)
		return (NULL);
	total_size = nmemb * size;
	allocated_mem = malloc(total_size);
	if (!allocated_mem)
		return (NULL);
	ft_bzero(allocated_mem, total_size);
	return ((void *)allocated_mem);
}
