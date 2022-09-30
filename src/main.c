/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:17 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 13:11:19 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	set_img(t_image *image, t_vars *data, int w, int h)
{
	image->mlx_img = mlx_new_image(data->mlx, w, h);
	image->addr = mlx_get_data_addr(image->mlx_img, \
	&(image->bits_per_pix), &(image->line_len), &(image->endian));
}

int	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bits_per_pix - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bits_per_pix / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pix - 8 - i)) & 0xFF;
		i -= 8;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	vars.move = 0;
	vars.av = av;
	vars.ac = ac;
	if (!init_data(ac, av, &vars.data))
		return (printf("--> ERROR INPUT\n"));
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRt !!");
	if (!vars.win)
		return (1);
	set_img(&vars.image, &vars, WIDTH, HEIGHT);
	mlx_loop_hook(vars.mlx, &handle_event, &vars);
	mlx_key_hook(vars.win, key_event, &vars);
	mlx_hook(vars.win, 17, 1L >> 17, loop_end, &vars);
	mlx_loop(vars.mlx);
	destroy(&vars);
	free_data(&vars.data);
}
