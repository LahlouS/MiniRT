/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:54:00 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/08 15:16:40 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	into_radius(t_vector *rslt, t_vector base, float radius)
{
	if ((radius + 0.012) - norme(sub_vector(base, *rslt)) <= 0)
		return (0);
	return (1);
}

void	init_plan(t_plan *plan, t_cylindre *cl, float normal_dir)
{
	if (normal_dir == -1)
		eq_vector(&plan->origin, cl->base);
	else
		eq_vector(&plan->origin, add_vector(cl->base, \
		float_x_vector(normalize(cl->dir), cl->heigth)));
	eq_vector(&plan->normal_vec, \
	float_x_vector(normalize(cl->dir), normal_dir));
	eq_vector(&plan->color, cl->color);
}
