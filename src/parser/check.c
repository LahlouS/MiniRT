/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:33:54 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 13:21:45 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	is_good_extension(char *str)
{
	char	*ext;
	int		i;

	i = 0;
	ext = ".rt";
	while (str && str[i] && str[i] != '.')
		i++;
	if (ft_strcmp(str + i, ext) == 0)
		return (1);
	return (0);
}

int	check_id(char *str)
{
	if (ft_strcmp(str, "A") == 0 || ft_strcmp(str, "C") == 0
		|| ft_strcmp(str, "L") == 0 || ft_strcmp(str, "sp") == 0
		|| ft_strcmp(str, "cy") == 0 || ft_strcmp(str, "pl") == 0)
		return (1);
	return (0);
}

int	check_range_vector(t_vector *vector, int min, int max)
{
	if ((vector->x < min || vector->x > max)
		|| ((vector->y < min || vector->y > max))
		|| (vector->z < min || vector->z > max))
		return (0);
	return (1);
}

int	check_range_object(t_Objects *temp)
{
	while (temp)
	{
		if (temp->id == SP)
		{
			if (!check_range_vector(&((t_Sphere *)temp->object)->color, 0, 255))
				return (0);
		}
		else if (temp->id == PL)
		{
			if (!check_range_vector(&((t_plan *)temp->object)->color, 0, 255))
				return (0);
		}
		else if (temp->id == CL)
			if (!check_range_vector(&((t_cylindre *)temp->object)->color, \
			0, 255))
				return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_acl(t_data *data)
{
	if (!data->luma || !data->lum || !data->cam || !data->objects)
		return (0);
	if ((data->luma->ratio < 0 || data->luma->ratio > 1)
		|| !check_range_vector(&data->luma->color, 0, 255))
		return (0);
	if ((data->lum->ratio < 0 || data->lum->ratio > 1)
		|| !check_range_vector(&data->lum->color, 0, 255))
		return (0);
	if ((data->cam->fov < 0 || data->cam->fov > 180)
		|| !check_range_vector(&data->cam->dir, -1, 1))
		return (0);
	if (data->objects)
		if (!check_range_object(data->objects))
			return (0);
	return (1);
}
