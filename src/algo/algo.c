/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:53:31 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/09 15:39:55 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	shift_color(t_vector color)
{
	int	res;

	res = 0;
	res |= ((int)min(255, max(0, color.x))) << 16;
	res |= ((int)min(255, max(0, color.y))) << 8;
	res |= ((int)min(255, max(0, color.z)));
	return (res);
}

float	get_intersection(t_Objects *temp, t_vector raydir, \
t_vector cam_pos, t_vector *phit)
{
	if (temp->id == SP)
	{
		return (inter_sphere(raydir, cam_pos, temp->object, phit));
	}
	if (temp->id == PL)
	{
		return (inter_plan(raydir, cam_pos, temp->object, phit));
	}
	if (temp->id == CL)
	{
		return (inter_cylindre(raydir, cam_pos, temp->object, phit));
	}
	return (0);
}

t_vector	loop_object_hit(t_Objects **objects, \
t_vector ray_dir, t_vector cam_pos, float *t_min)
{
	t_Objects	*temp;
	t_vector	p_hit;
	t_vector	p_hit_temp;
	float		t;

	temp = *objects;
	*t_min = FLT_MAX;
	while (temp)
	{
		t = get_intersection(temp, ray_dir, cam_pos, &p_hit_temp);
		if (t && t < *t_min)
		{
			eq_vector(&p_hit, p_hit_temp);
			*t_min = t;
			*objects = temp;
		}
		temp = temp->next;
	}
	return (p_hit);
}

t_vector	pix_pos(int j, int i, float fov)
{
	t_vector	pixel;

	pixel.x = j - WIDTH / 2;
	pixel.y = i - HEIGHT / 2;
	pixel.z = -1 * (WIDTH) / (2 * tanf((fov * PI) / 360));
	return (normalize(pixel));
}

void	algo(t_vars *vars)
{
	t_matrix	matrix;
	t_vector	v[NB_VEC];
	int			i;
	int			j;
	float		t_min;

	i = -1;
	eq_matrix(&matrix, \
	get_transfo_matrix(vars->data.cam->pos, vars->data.cam->dir));
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			eq_vector(&v[RAY_DIR], pix_pos(j, i, (float)vars->data.cam->fov));
			eq_vector(&v[RAY_DIR], vector_x_matrix(v[RAY_DIR], matrix, 0));
			eq_vector(&v[HIT_POINT], loop_object_hit(&vars->data.objects, \
			v[RAY_DIR], vars->data.cam->pos, &t_min));
			if (t_min == FLT_MAX)
				img_pix_put(&vars->image, j, i, BACK_GROUND);
			else
				algo_shadow(vars, v[HIT_POINT], i, j);
			rewind_list(&(vars->data.objects));
		}
	}
}
