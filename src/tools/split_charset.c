/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:16:41 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/07 18:20:15 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	ft_o(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_find_nbstr(char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	while (1)
	{
		if (ft_o(str[i], charset) && !ft_o(str[i - 1], charset))
			count++;
		if (str[i] == '\0' && !ft_o(str[i - 1], charset))
			count++;
		if (!str[i])
			return (count);
		i++;
	}
	return (0);
}

char	*ft_init_str(char *str, int e)
{
	char	*to_ret;
	int		i;

	i = -1;
	to_ret = malloc(sizeof(char) * (e + 1));
	if (!to_ret)
		return (NULL);
	while (++i < e)
		to_ret[i] = str[i];
	to_ret[i] = '\0';
	return (to_ret);
}

char	*ft_get_str(char *str, char *charset, int i)
{
	int		e;
	int		a;
	char	*to_ret;

	a = 0;
	while (a <= i)
	{
		e = 0;
		while (ft_o(*str, charset))
			str++;
		while (!ft_o(str[e], charset) && str[e])
			e++;
		if (*str != str[e] && a == i)
		{
			to_ret = ft_init_str(str, e);
			return (to_ret);
		}
		str += e;
		a++;
	}
	return (NULL);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		nbstr;
	int		i;
	char	**strs;

	i = -1;
	nbstr = ft_find_nbstr(str, charset);
	strs = malloc(sizeof(char *) * (nbstr + 1));
	if (!strs)
		return (NULL);
	while (++i < nbstr)
		*(strs + i) = ft_get_str(str, charset, i);
	*(strs + i) = 0;
	return (strs);
}
