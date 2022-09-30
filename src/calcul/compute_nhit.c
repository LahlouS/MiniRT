/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_nhit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:16:53 by slahlou           #+#    #+#             */
/*   Updated: 2022/09/09 14:22:08 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

t_vector	compute_nhit_sp(t_Sphere *sp, t_vector hit_point, t_vector cam_pos)
{
	t_vector	n_hit;

	eq_vector(&n_hit, normalize(sub_vector(hit_point, sp->center)));
	if (norme(sub_vector(cam_pos, sp->center)) < sp->radius)
		eq_vector(&n_hit, float_x_vector(n_hit, -1));
	return (n_hit);
}

t_vector	compute_nhit_cy(t_cylindre *cy, \
t_vector hit_point, t_vector cam_pos)
{
	t_vector	n_hit;

	eq_vector(&n_hit, get_nhit_cl(cy, hit_point));
	if (scalaire_product(normalize(sub_vector(hit_point, cam_pos)), n_hit) > 0)
		eq_vector(&n_hit, float_x_vector(n_hit, -1));
	return (n_hit);
}

t_vector	compute_nhit_pl(t_plan *pl, t_vector hit_point, t_vector cam_pos)
{
	t_vector	n_hit;

	eq_vector(&n_hit, normalize(pl->normal_vec));
	if (scalaire_product(normalize(sub_vector(hit_point, cam_pos)), n_hit) > 0)
		eq_vector(&n_hit, float_x_vector(n_hit, -1));
	return (n_hit);
}
