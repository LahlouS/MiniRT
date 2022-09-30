/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:41:30 by meudier           #+#    #+#             */
/*   Updated: 2022/09/08 17:57:48 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	destroy(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.mlx_img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free (vars->mlx);
	return (0);
}
