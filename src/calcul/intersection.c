/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:54:32 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/09 13:50:40 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

float	inter_sphere(t_vector dir_pix, t_vector cam_o, void *sphere, \
t_vector *rslt)
{
	t_vector	oc;
	t_equation	inter;
	t_Sphere	*sp;

	sp = (t_Sphere *)sphere;
	eq_vector(&oc, sub_vector(cam_o, sp->center));
	eq_vector(&dir_pix, normalize(dir_pix));
	inter.b = scalaire_product(dir_pix, oc) * 2;
	inter.c = (scalaire_product(oc, oc) - (sp->radius * sp->radius));
	inter.delta = (inter.b * inter.b) - (4 * inter.c);
	if (inter.delta >= 0)
	{
		inter.t1 = ((inter.b * -1) - sqrtf(inter.delta)) / 2;
		inter.t2 = ((inter.b * -1) + sqrtf(inter.delta)) / 2;
		if (inter.t2 < 0)
			return (0);
		if (inter.t1 > 0)
			inter.t = inter.t1;
		else
			inter.t = inter.t2;
		eq_vector(rslt, add_vector(cam_o, float_x_vector(dir_pix, inter.t)));
	}
	else
		return (0);
	return (inter.t);
}

float	inter_plan(t_vector dir_pix, t_vector cam_o, void *plan, t_vector *rslt)
{
	t_plan		*pl;
	float		d;
	float		t;
	t_vector	pl_normal;

	t = 0;
	d = 0;
	pl = (t_plan *)plan;
	eq_vector(&pl_normal, normalize(pl->normal_vec));
	d = ((pl->origin.x * pl_normal.x) + (pl->origin.y * pl_normal.y) + \
	(pl->origin.z * pl_normal.z)) * -1;
	if (scalaire_product(pl_normal, dir_pix))
		t = -1 * ((scalaire_product(pl_normal, cam_o) + d) / \
		(scalaire_product(pl_normal, dir_pix)));
	eq_vector(rslt, add_vector(cam_o, float_x_vector(dir_pix, t)));
	return ((t > 0) * t);
}

float	inter_ext_cl(t_vector dir_pix, t_vector cam_o, \
t_cylindre *cl, t_vector *rslt)
{
	t_equation	var;
	t_vector	va;
	t_vector	rao;

	eq_vector(&dir_pix, normalize(dir_pix));
	eq_vector(&cl->dir, normalize(cl->dir));
	eq_vector(&va, cross_product(cross_product(cl->dir, dir_pix), cl->dir));
	eq_vector(&rao, cross_product(cross_product(cl->dir, \
	sub_vector(cam_o, cl->base)), cl->dir));
	var.a = scalaire_product(va, va);
	var.b = 2 * scalaire_product(rao, va);
	var.c = scalaire_product(rao, rao) - (cl->radius * cl->radius);
	var.delta = var.b * var.b - 4 * var.a * var.c;
	if (var.delta >= 0)
	{
		var.t1 = ((var.b * -1) - sqrtf(var.delta)) / (2 * var.a);
		var.t2 = ((var.b * -1) + sqrtf(var.delta)) / (2 * var.a);
		if (var.t2 < 0)
			return (0);
		var.t = (var.t1 > 0) * var.t1 + (var.t2 > 0 && var.t1 <= 0) * var.t2;
		eq_vector(rslt, add_vector(cam_o, float_x_vector(dir_pix, var.t)));
		return (var.t);
	}
	else
		return (0);
}

float	inter_circle_cl(t_cylindre *cl, \
t_vector dir_pix, t_vector cam_o, t_vector *rslt)
{
	t_equation	var;
	t_plan		base;
	t_plan		end;
	t_vector	base_rslt;
	t_vector	end_rslt;

	init_plan(&base, cl, -1);
	init_plan(&end, cl, 1);
	var.t1 = inter_plan(dir_pix, cam_o, &base, &base_rslt);
	var.t2 = inter_plan(dir_pix, cam_o, &end, &end_rslt);
	if (var.t1 && (!var.t2 || var.t1 < var.t2) && var.t1 != \
	FLT_MAX && into_radius(&base_rslt, base.origin, cl->radius))
	{
		eq_vector(rslt, base_rslt);
		cl->inter_code = 2;
		return (var.t1);
	}
	if (var.t2 && (!var.t1 || var.t2 < var.t1) && var.t2 != \
	FLT_MAX && into_radius(&end_rslt, end.origin, cl->radius))
	{
		eq_vector(rslt, end_rslt);
		cl->inter_code = 3;
		return (var.t2);
	}
	return (0);
}

float	inter_cylindre(t_vector dir_pix, t_vector cam_o, \
void *cylindre, t_vector *rslt)
{
	t_cylindre	*cl;
	float		hyp;
	float		h;
	float		t;

	cl = (t_cylindre *)cylindre;
	t = inter_ext_cl(dir_pix, cam_o, cl, rslt);
	if (t)
	{
		hyp = norme(sub_vector(*rslt, cl->base));
		h = sqrtf((hyp * hyp) - (cl->radius * cl->radius));
	}
	if (t && h < cl->heigth && scalaire_product(sub_vector(*rslt, cl->base), \
	cl->dir) > 0)
	{
		cl->inter_code = 1;
		return (t);
	}
	return (inter_circle_cl(cl, dir_pix, cam_o, rslt));
}
