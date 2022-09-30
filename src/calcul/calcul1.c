/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:25:34 by meudier           #+#    #+#             */
/*   Updated: 2022/09/01 12:29:51 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

t_vector	float_x_vector(t_vector v1, float k)
{
	t_vector	rslt;

	rslt.x = v1.x * k;
	rslt.y = v1.y * k;
	rslt.z = v1.z * k;
	return (rslt);
}

t_vector	vector_x_vector(t_vector v1, t_vector v2)
{
	t_vector	rslt;

	rslt.x = v1.x * v2.x;
	rslt.y = v1.y * v2.y;
	rslt.z = v1.z * v2.z;
	return (rslt);
}

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	rslt;

	rslt.x = v1.x + v2.x;
	rslt.y = v1.y + v2.y;
	rslt.z = v1.z + v2.z;
	return (rslt);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	rslt;

	rslt.x = v1.y * v2.z - v1.z * v2.y;
	rslt.y = v1.z * v2.x - v1.x * v2.z;
	rslt.z = v1.x * v2.y - v1.y * v2.x;
	return (rslt);
}

t_vector	sub_vector(t_vector v1, t_vector v2)
{
	return (add_vector(v1, float_x_vector(v2, -1)));
}
