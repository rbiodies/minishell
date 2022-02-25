/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:46:20 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/16 17:04:21 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reverse(char *buffer)
{
	int		i;
	int		j;
	char	k;

	i = 0;
	j = 0;
	while (buffer[i] != '\0')
		i++;
	i--;
	while (i > j)
	{
		k = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = k;
		j++;
		i--;
	}
	return (buffer);
}

static int	ft_len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static char	*ft_zapolnenie(char *buffer, long nb, int sign)
{
	int	i;

	i = 0;
	if (nb == 0)
		buffer[i++] = 0 + '0';
	while (nb > 0)
	{
		buffer[i++] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign == -2147483648)
		buffer[i++] = '2';
	if (sign < 0)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*buffer;
	long	nb;

	sign = 0;
	nb = n;
	buffer = (char *)malloc(ft_len(nb) + 1);
	if (buffer == NULL)
		return (0);
	if (nb == -2147483648)
	{
		sign = nb;
		nb = 147483648;
	}
	else if (nb < 0)
	{
		sign = nb;
		nb = -nb;
	}
	buffer = ft_zapolnenie(buffer, nb, sign);
	buffer = ft_reverse(buffer);
	return (buffer);
}	
