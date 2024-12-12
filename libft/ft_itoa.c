/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:55:53 by jpyciarz          #+#    #+#             */
/*   Updated: 2024/03/12 12:49:02 by jpyciarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i = 1;
		nb *= -1;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	writenum(int nb, char *result, int *i)
{
	if (nb == -2147483648)
	{
		result[(*i)++] = '-';
		result[(*i)++] = '2';
		nb = 147483648;
	}
	if (nb < 0)
	{
		result[(*i)++] = '-';
		nb = -nb;
	}
	if (nb >= 10)
	{
		writenum(nb / 10, result, i);
		writenum(nb % 10, result, i);
	}
	else
	{
		result[(*i)++] = nb + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	result = malloc((digit_count(n) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	writenum(n, result, &i);
	result[i] = '\0';
	return (result);
}
