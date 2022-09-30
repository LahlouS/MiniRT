/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:31:54 by meudier           #+#    #+#             */
/*   Updated: 2022/08/30 17:39:06 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_cpy_buf(char *buf, int len)
{
	char	*temp;

	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	temp[len] = 0;
	while (--len >= 0)
		temp[len] = buf[len];
	return (temp);
}

char	*ft_cat_buf_to_str(char *str, char *buf, int str_len, int buf_len)
{
	char	*temp;
	int		i;
	int		e;

	temp = malloc(sizeof(char) * (str_len + buf_len + 1));
	if (!temp)
		return (NULL);
	e = 0;
	while (str[e])
	{
		temp[e] = str[e];
		e++;
	}
	i = 0;
	while (buf[i])
	{
		temp[e] = buf[i];
		i++;
		e++;
	}
	temp[e] = '\0';
	return (temp);
}
