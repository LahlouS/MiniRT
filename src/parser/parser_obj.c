/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:01:59 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 13:47:37 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	ft_parse_sp(t_data *data, char **line_split)
{
	t_Sphere	*temp;
	int			j;
	int			res;

	temp = malloc(sizeof(t_Sphere));
	res = 1;
	if (!temp)
		res = 0;
	j = 0;
	while (line_split[j])
		j++;
	if (j != 4)
		res = 0;
	if (res && !a_to_vec(line_split[1], &temp->center, &is_float))
		res = 0;
	if (res && !a_to_vec(line_split[3], &temp->color, &is_digit))
		res = 0;
	if (res && !is_float(line_split[2]))
		res = 0;
	if (res)
		temp->radius = (ft_atof(line_split[2])) / 2;
	if (!res || !__add_node(&data->objects, (void *)temp, SP))
		return (free_void(temp));
	return (1);
}

void	increment_j(char **line_split, int *j)
{
	*j = 0;
	while (line_split[*j])
		(*j)++;
}

int	ft_parse_cl(t_data *data, char **line_split)
{
	t_cylindre	*temp;
	int			j;
	int			res;

	temp = malloc(sizeof(t_cylindre));
	res = 1;
	if (!temp)
		res = 0;
	increment_j(line_split, &j);
	if (j != 6)
		res = 0;
	if (res && !a_to_vec(line_split[1], &temp->base, &is_float))
		res = 0;
	if (res && !a_to_vec(line_split[2], &temp->dir, &is_float))
		res = 0;
	if (res && !a_to_vec(line_split[5], &temp->color, &is_digit))
		res = 0;
	if (res)
		temp->radius = (ft_atof(line_split[3])) / 2;
	if (res)
		temp->heigth = (ft_atof(line_split[4]));
	if (!res || !__add_node(&data->objects, (void *)temp, CL))
		return (free_void(temp));
	return (1);
}

int	ft_parse_pl(t_data *data, char **line_split)
{
	t_plan	*temp;
	int		j;
	int		res;

	temp = malloc(sizeof(t_plan));
	res = 1;
	if (!temp)
		res = 0;
	j = 0;
	while (line_split[j])
		j++;
	if (j != 4)
		res = 0;
	if (res && !a_to_vec(line_split[1], &temp->origin, &is_float))
		res = 0;
	if (res && !a_to_vec(line_split[2], &temp->normal_vec, &is_float))
		res = 0;
	if (res && !a_to_vec(line_split[3], &temp->color, &is_digit))
		res = 0;
	if (!res || !__add_node(&data->objects, (void *)temp, PL))
		return (free_void(temp));
	return (1);
}

int	a_to_vec(char *str, t_vector *vector, int (*f)(char *))
{
	char	**temp;
	int		i;

	temp = ft_split (str, ',');
	if (!temp)
		return (0);
	i = 0;
	while (temp && temp[i])
	{
		if (!(*f)(temp[i]) || i >= 3)
			return (free_tab(temp));
		i++;
	}
	if (i != 3)
		return (free_tab(temp));
	vector->x = ft_atof(temp[0]);
	vector->y = ft_atof(temp[1]);
	vector->z = ft_atof(temp[2]);
	free_tab(temp);
	return (1);
}
