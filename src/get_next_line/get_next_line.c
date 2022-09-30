/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:29:50 by meudier           #+#    #+#             */
/*   Updated: 2022/08/30 17:39:43 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_malloc_and_cat(char *buf, char **str)
{
	int		i;
	int		e;
	char	*temp;

	i = 0;
	while (buf[i])
		i++;
	if (!(*str) && i)
		*str = ft_cpy_buf(buf, i);
	else if ((*str))
	{
		e = 0;
		while ((*str)[e])
			e++;
		temp = ft_cat_buf_to_str(*str, buf, e, i);
		free(*str);
		(*str) = temp;
	}
	else
		*str = NULL;
}

int	ft_check_new_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_clean_str(char **str, char *buf)
{
	int		i;
	int		e;
	char	*ret;

	if (!(*str))
		return (NULL);
	i = 0;
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	ret = malloc(sizeof(char) * (i + 2));
	i = -1;
	while ((*str)[++i] != '\n' && (*str)[i])
		ret[i] = (*str)[i];
	ret[i] = '\0';
	e = i;
	i = 0;
	while ((*str)[++e])
	{
		buf[i] = (*str)[e];
		i++;
	}
	buf[i] = 0;
	free(*str);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "\0";
	char		*str;
	int			read_ret;

	if ((fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	read_ret = 1;
	ft_malloc_and_cat(buf, &str);
	while ((read_ret) && ft_check_new_line(buf))
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret < 0)
		{
			free(str);
			return (NULL);
		}
		buf[read_ret] = '\0';
		if (read_ret)
			ft_malloc_and_cat(buf, &str);
	}
	if (read_ret)
		return (ft_clean_str(&str, buf));
	else
		return (str);
}
