/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:56:35 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 18:17:05 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

int	free_void(void *a)
{
	free(a);
	return (0);
}

int	free_data(t_data *data)
{
	t_Objects	*temp;

	if (data->luma)
		free(data->luma);
	if (data->lum)
		free(data->lum);
	if (data->cam)
		free(data->cam);
	if (data->objects)
	{
		while (data->objects)
		{
			temp = (data->objects);
			if (data->objects->object)
				free(data->objects->object);
			data->objects = data->objects->next;
			free(temp);
			temp = NULL;
		}
	}
	data->lum = NULL;
	data->luma = NULL;
	data->cam = NULL;
	return (0);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}
