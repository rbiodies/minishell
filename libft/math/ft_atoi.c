/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:45:14 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/16 10:55:46 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (((unsigned char *)s1)[i] != '\0' && ((unsigned char *)s2)[i] != '\0' \
			&& n != 0 && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
	{
		i++;
		n--;
	}
	if (i != 0 && (((unsigned char *)s1)[i] == '\0' \
				|| ((unsigned char *)s2)[i] == '\0'))
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

static int	ft_longlong(const char *str, int a, int sign, int digits)
{
	if (a >= 19)
	{
		if (sign > 0)
		{
			if (ft_strncmp((str - a), "9223372036854775807", 19) >= 0 || a > 19)
				return (-1);
		}
		else
		{
			if (ft_strncmp((str - a), "9223372036854775808", 19) < 0 || a > 19)
				return (0);
		}
	}
	return (digits);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	digits;
	int	a;

	sign = 1;
	digits = 0;
	a = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digits = digits * 10 + sign * (*str - 48);
		str++;
		a++;
	}
	digits = ft_longlong(str, a, sign, digits);
	return (digits);
}
