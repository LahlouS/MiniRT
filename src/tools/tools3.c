/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:24:34 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/09 15:36:35 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	join = (char *)malloc(sizeof(char) * size + 1);
	if (!join)
		return (NULL);
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

int	ft_count(int n)
{
	long int	big_n;
	int			count;

	count = 1;
	big_n = n;
	if (n < 0)
	{
		big_n = -big_n;
		count++;
	}
	else
		big_n = n;
	while (big_n >= 10)
	{
		count++;
		big_n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	big_n;
	int			count;
	char		*ascii;

	count = ft_count(n);
	big_n = n;
	ascii = (char *)malloc((count + 1) * sizeof(char));
	if (!ascii)
		return (NULL);
	ascii[count] = '\0';
	if (n == 0)
		ascii[0] = '0';
	else if (n < 0)
	{
		ascii[0] = '-';
		big_n *= -1;
	}
	while (big_n > 0 && --count >= 0)
	{
		ascii[count] = big_n % 10 + '0';
		big_n = big_n / 10;
	}
	return (ascii);
}

char	*ftoa(float f)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	f *= 10;
	temp = ft_itoa((int) f);
	str = malloc(ft_strlen(temp) + 2);
	while (temp[i])
	{
		if (!temp[i + 1])
		{
			str[i++] = '.';
			str[i] = temp[i - 1];
			i++;
			break ;
		}
		str[i] = temp[i];
		i++;
	}
	str[i] = 0;
	free(temp);
	return (str);
}

void	rewind_list(t_Objects **obj)
{
	t_Objects	*tmp;

	tmp = *obj;
	if (tmp)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		(*obj) = tmp;
	}
}
