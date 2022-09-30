/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:21:12 by meudier           #+#    #+#             */
/*   Updated: 2022/08/30 18:44:48 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

t_vector	normalize(t_vector v1)
{
	return (float_x_vector(v1, 1 / norme(v1)));
}

float	scalaire_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	norme(t_vector v1)
{
	return (sqrtf(scalaire_product(v1, v1)));
}

void	eq_vector(t_vector *v1, t_vector v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
	v1->z = v2.z;
}
