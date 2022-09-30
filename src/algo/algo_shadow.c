/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:50:22 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/09 16:54:19 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

t_vector	get_luminosity(t_vars *vars, t_vector hit_point, \
t_vector n_hit, float transmission)
{
	t_vector	luminosity;
	t_vector	lum_dir;
	t_vector	p_lum;
	float		ld;
	float		la;

	eq_vector(&p_lum, sub_vector(vars->data.lum->pos, hit_point));
	eq_vector(&lum_dir, normalize(p_lum));
	if (transmission == FLT_MAX || transmission > norme(p_lum))
		transmission = 1;
	else
		transmission = 0.8;
	ld = transmission * (vars->data.lum->ratio * (1000000.0 / \
	scalaire_product(p_lum, p_lum))) * max(0, scalaire_product(n_hit, lum_dir));
	la = (100.0 * vars->data.luma->ratio);
	luminosity.x = 255 - (vars->data.lum->color.x * (ld / 255)) - \
	(vars->data.luma->color.x * (la / 255));
	luminosity.y = 255 - (vars->data.lum->color.y * (ld / 255)) - \
	(vars->data.luma->color.y * (la / 255));
	luminosity.z = 255 - (vars->data.lum->color.z * (ld / 255)) - \
	(vars->data.luma->color.z * (la / 255));
	return (luminosity);
}

t_vector	check_obstruction(t_vars *vars, t_vector hit_point, \
t_vector n_hit, t_Objects *objects)
{
	t_vector	lum_dir;
	float		transmission;
	t_Objects	*current;

	current = objects;
	eq_vector(&lum_dir, normalize(sub_vector(vars->data.lum->pos, hit_point)));
	rewind_list(&objects);
	loop_object_hit(&objects, lum_dir, add_vector(hit_point, \
	float_x_vector(n_hit, 0.01)), &transmission);
	if (current->id == SP)
		return (sub_vector(((t_Sphere *)current->object)->color, \
		get_luminosity(vars, hit_point, n_hit, transmission)));
	else if (current->id == PL)
		return (sub_vector(((t_plan *)current->object)->color, \
		get_luminosity(vars, hit_point, n_hit, transmission)));
	else if (current->id == CL)
		return (sub_vector(((t_cylindre *)current->object)->color, \
		get_luminosity(vars, hit_point, n_hit, transmission)));
	else
		return (((t_Sphere *)current->object)->color);
}

t_vector	get_nhit_cl(t_cylindre *cl, t_vector hit_point)
{
	t_vector	b_phit;
	t_vector	n_hit;
	float		hyp;
	float		h;

	eq_vector(&b_phit, sub_vector(hit_point, cl->base));
	eq_vector(&cl->dir, normalize(cl->dir));
	hyp = norme(b_phit);
	h = sqrtf((hyp * hyp) - (cl->radius * cl->radius));
	if (cl->inter_code == 1)
		eq_vector(&n_hit, normalize(sub_vector(hit_point, \
		add_vector(cl->base, float_x_vector(cl->dir, h)))));
	else if (cl->inter_code == 2)
		eq_vector(&n_hit, float_x_vector(cl->dir, -1));
	else
		eq_vector(&n_hit, cl->dir);
	return (n_hit);
}

void	algo_shadow(t_vars *vars, t_vector hit_point, int i, int j)
{
	t_vector	n_hit;

	if (vars->data.objects->id == SP)
		eq_vector(&n_hit, \
		compute_nhit_sp(((t_Sphere *)vars->data.objects->object), \
		hit_point, vars->data.cam->pos));
	else if (vars->data.objects->id == PL)
		eq_vector(&n_hit, \
		compute_nhit_pl(((t_plan *)vars->data.objects->object), \
		hit_point, vars->data.cam->pos));
	else if (vars->data.objects->id == CL)
		eq_vector(&n_hit, \
		compute_nhit_cy((t_cylindre *)vars->data.objects->object, \
		hit_point, vars->data.cam->pos));
	img_pix_put(&vars->image, j, i, shift_color(check_obstruction(vars, \
	hit_point, n_hit, vars->data.objects)));
}
