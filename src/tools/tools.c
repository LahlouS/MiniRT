/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:58:56 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 10:17:05 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (1 && s1 && s2)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	is_float(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] == '.')
	{
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
	}
	while (*nptr && !(*nptr >= '0' && *nptr <= '9'))
		nptr++;
	while (*nptr && *nptr <= '9' && *nptr >= '0')
	{
		res = res * 10 + ((*nptr) - 48);
		nptr++;
	}
	return (res * sign);
}

float	ft_atof(char *str)
{
	float	res;
	float	res2;
	int		sign;

	sign = 1;
	if (str && *str == '-')
	{
		sign = -1;
		str++;
	}
	res = (float) ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	res2 = (float) ft_atoi(str);
	while (res2 >= 1)
		res2 /= 10;
	return ((res + res2) * sign);
}
