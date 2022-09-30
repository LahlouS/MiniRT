/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:13:34 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 13:52:57 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	handle_event(t_vars *vars)
{
	if (vars->move)
	{
		vars->move = 0;
		algo(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, \
		vars->image.mlx_img, 0, 0);
	}
	return (0);
}

int	key_event(int keycode, t_vars *vars)
{
	if (keycode == 65293 && vars->av)
	{
		free_data(&vars->data);
		if (!init_data(2, vars->av, &vars->data))
			printf("--> ERROR INPUT\n");
		else
			vars->move = 1;
	}
	if (keycode == XK_Escape)
		return (loop_end(vars));
	return (0);
}

int	loop_end(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}
