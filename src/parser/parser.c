/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:04:49 by meudier           #+#    #+#             */
/*   Updated: 2022/09/07 18:24:22 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	ft_parse_a(t_data *data, char **line_split)
{
	int	j;

	j = 0;
	while (line_split[j])
		j++;
	if (j != 3 || data->luma || !is_float(line_split[1]))
		return (0);
	data->luma = malloc(sizeof(t_LumA));
	if (!data->luma)
		return (0);
	if (!is_float(line_split[1]))
		return (0);
	data->luma->ratio = ft_atof(line_split[1]);
	if (!a_to_vec(line_split[2], &data->luma->color, &is_digit))
		return (0);
	return (1);
}

int	ft_parse_c(t_data *data, char **line_split)
{
	int	j;

	j = 0;
	while (line_split[j])
		j++;
	if (j != 4 || data->cam)
		return (0);
	data->cam = malloc(sizeof(t_Cam));
	if (!data->cam)
		return (0);
	if (!a_to_vec(line_split[1], &data->cam->pos, &is_float))
		return (0);
	if (!a_to_vec(line_split[2], &data->cam->dir, &is_float))
		return (0);
	if (!is_digit(line_split[3]))
		return (0);
	data->cam->fov = ft_atoi(line_split[3]);
	return (1);
}

int	ft_parse_l(t_data *data, char **line_split)
{
	int	j;

	j = 0;
	while (line_split[j])
		j++;
	if (j != 4 || data->lum)
		return (0);
	data->lum = malloc(sizeof(t_Lum));
	if (!data->lum)
		return (0);
	if (!a_to_vec(line_split[1], &data->lum->pos, &is_float))
		return (0);
	if (!a_to_vec(line_split[3], &data->lum->color, &is_digit))
		return (0);
	if (!is_float(line_split[2]))
		return (0);
	data->lum->ratio = ft_atof(line_split[2]);
	return (1);
}

void	init_ft_parse(int (*parse_line['s' + 1])(t_data *, char**))
{
	parse_line['A'] = &ft_parse_a;
	parse_line['C'] = &ft_parse_c;
	parse_line['L'] = &ft_parse_l;
	parse_line['s'] = &ft_parse_sp;
	parse_line['c'] = ft_parse_cl;
	parse_line['p'] = ft_parse_pl;
}

int	parse(char *line, t_data *data)
{
	char	**line_split;
	int		(*parse_line['s' + 1])(t_data *, char **);

	init_ft_parse(parse_line);
	line_split = ft_split_charset(line, " \t");
	if (check_id(*line_split))
	{
		if (!(*parse_line[(int)*line])(data, line_split))
		{
			free_tab(line_split);
			return (0);
		}
	}
	free_tab(line_split);
	return (1);
}
