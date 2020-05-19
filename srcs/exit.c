/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:31 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:14:29 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_program(t_data *data, char *error_msg, char *str)
{
	if (ft_memcmp(str, "\\o/\n", 4))
		ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd(str, 1);
	free_settings(&data->maps);
	if (data->maps.done)
	{
		free_frame(data, &data->ray);
		mlx_destroy_image(data->mlx, data->img.ptr);
		mlx_destroy_window(data->mlx, data->window);
	}
	ft_putstr_fd("\n_END_OF_PROGRAM_\n", 1);
	exit(0);
	return (0);
}

void	free_frame(t_data *data, t_ray *ray)
{
	mlx_destroy_image(data->mlx, data->ray.NO_img.ptr);
	mlx_destroy_image(data->mlx, data->ray.SO_img.ptr);
	mlx_destroy_image(data->mlx, data->ray.EA_img.ptr);
	mlx_destroy_image(data->mlx, data->ray.WE_img.ptr);
	mlx_destroy_image(data->mlx, data->ray.S_img.ptr);
	free(ray->z_buffer);
	ray->z_buffer = NULL;
	free(ray->spr_order);
	ray->spr_order = NULL;
	free(ray->spr_dist);
	ray->spr_dist = NULL;
}

void	free_sprites(t_maps *maps)
{
	if (maps->spr_x != NULL)
		free(maps->spr_x);
	if (maps->spr_y != NULL)
		free(maps->spr_y);
	if (maps->spr_text != NULL)
		free(maps->spr_text);
	maps->spr_x = NULL;
	maps->spr_y = NULL;
	maps->spr_text = NULL;
}

void	free_settings(t_maps *maps)
{
	if (maps->NO_path != NULL)
		free(maps->NO_path);
	if (maps->SO_path != NULL)
		free(maps->SO_path);
	if (maps->WE_path != NULL)
		free(maps->WE_path);
	if (maps->EA_path != NULL)
		free(maps->EA_path);
	if (maps->S_path != NULL)
		free(maps->S_path);
	maps->NO_path = NULL;
	maps->SO_path = NULL;
	maps->WE_path = NULL;
	maps->EA_path = NULL;
	maps->S_path = NULL;
	free_sprites(maps);
	free_map(maps);
}

void	free_map(t_maps *maps)
{
	int i;

	i = 0;
	if (maps->map != NULL)
	{
		while (i < maps->map_size.y)
		{
			if (maps->map[i] != NULL)
			{
				free(maps->map[i]);
				maps->map[i] = NULL;
			}
			i++;
		}
		free(maps->map);
		maps->map = NULL;
	}
}
