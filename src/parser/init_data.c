/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:12:15 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 13:31:21 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	__add_node(t_Objects **data, void *current, int id)
{
	t_Objects	*nouveau;
	t_Objects	*last;

	nouveau = malloc(sizeof(t_Objects));
	if (!nouveau)
		return (0);
	nouveau->id = id;
	nouveau->object = current;
	nouveau->next = NULL;
	nouveau->prev = NULL;
	if (!(*data))
		*data = nouveau;
	else
	{
		last = *data;
		while (last->next)
			last = last->next;
		last->next = nouveau;
		nouveau->prev = last;
	}
	return (1);
}

void	initialize_data(t_data *data)
{
	data->luma = NULL;
	data->lum = NULL;
	data->cam = NULL;
	data->objects = NULL;
}

int	init_data2(char *av, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	line = "start";
	ret = 1;
	initialize_data(data);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	while (line && ret)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (line[0] != '\n' && line[0])
				ret = parse(line, data);
			free(line);
		}
	}
	if (!ret || !check_acl(data))
		ret = free_data(data);
	close(fd);
	return (ret);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac == 2 && is_good_extension(av[1]))
		return (init_data2(av[1], data));
	return (0);
}
