/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 17:35:56 by kparis            #+#    #+#             */
/*   Updated: 2020/03/29 03:08:04 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_mlx *data, t_ray *ray)
{
	int x;

	x = 0;
	ray->dir_x = -1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;

	while (x < data->map->res_x)
	{
		ray->camera_x = 2 * x / (double)data->map->res_x - 1;
		ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;

		//which box of the map we're in
		ray->map_x = (int)data->map->pos_x;
		ray->map_y = (int)data->map->pos_y;

		ray->deltadist_x = (ray->raydir_y == 0) ? 0 : ((ray->raydir_x == 0) ? : fabs(1 / ray->raydir_x));
		ray->deltadist_y = (ray->raydir_x == 0) ? 0 : ((ray->raydir_y == 0) ? : fabs(1 / ray->raydir_y));
		ray->hit = 0;

		if (ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->sidedist_x = (data->map->pos_x - ray->map_x) * ray->deltadist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->sidedist_x = (ray->map_x + 1.0 - data->map->pos_x) * ray->deltadist_x;
		}
		if (ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->sidedist_y = (data->map->pos_y - ray->map_y) * ray->deltadist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->sidedist_y = (ray->map_y + 1.0 - data->map->pos_y) * ray->deltadist_y;
		}
		//dda
		while (ray->hit == 0)
		{
			if (ray->sidedist_x < ray->sidedist_y)
			{
				ray->sidedist_x += ray->deltadist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->sidedist_y += ray->deltadist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (data->map->map[ray->map_x][ray->map_y] > 0)
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - data->map->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
		else
			ray->perp_wall_dist = (ray->map_y - data->map->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;

		ray->line_height = (int)(data->map->res_y / ray->perp_wall_dist);

		ray->draw_start = (ray->line_height * -1) / 2 + data->map->res_y / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + data->map->res_y / 2;
		if (ray->draw_end >= data->map->res_y)
			ray->draw_end = data->map->res_y - 1;

		int color = 0x00FF0000;

		if (ray->side == 1)
			color = color / 2;

		while (ray->draw_start < ray->draw_end)
		{
			ft_mlx_pixel_put(data->img, x, ray->draw_start, color);
			ray->draw_start++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
}

int		loop(t_mlx *data)
{
	//button press ?
		//raycasting
	raycasting(data, data->ray);

	return (EXIT_SUCCESS);
}