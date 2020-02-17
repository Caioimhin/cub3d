/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:30:45 by kparis            #+#    #+#             */
/*   Updated: 2020/02/17 17:40:20 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int raycasting(t_mlx *data)
{
	int x;
	int y;
	//pts de départ de la cam
	double pos_x;
	double pos_y;
	//direction ou regarde la cam
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double camera_x;
	double raydir_x;
	double raydir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;

	x = 0;
	y = 0;
	pos_x = (double)data->player->player_x;
	pos_y = (double)data->player->player_y;
	dir_x = (double)data->player->player_dir_x;
	dir_y = (double)data->player->player_dir_y;
	plane_x = 0;
	plane_y = 0.66;
	hit = 0;

	if (data->key->key_up || data->key->key_down || data->key->key_left || data->key->key_right || data->player->rot_speed)
	{
		while (x <= data->map->res_x)
		{
			camera_x = 2 * x / (double)data->map->res_x - 1;
			raydir_x = dir_x + plane_x * camera_x;
			raydir_y = dir_y + plane_y * camera_x;

			map_x = (int)pos_x;
			map_y = (int)pos_y;
			delta_dist_x = (raydir_x == 0) ? 0 : ((raydir_x == 0) ? 1 : fabs(1 / raydir_x));
			delta_dist_y = (raydir_y == 0) ? 0 : ((raydir_y == 0) ? 1 : fabs(1 / raydir_y));

			if (raydir_x < 0)
			{
				step_x = -1;
				side_dist_x = (pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
			}
			if (raydir_y < 0)
			{
				step_y = -1;
				side_dist_y = (pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
			}

			//dda
			while (hit == 0)
			{
				if (side_dist_x < side_dist_y)
				{
					side_dist_x += delta_dist_x;
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += delta_dist_y;
					map_y += step_y;
					side = 1;
				}
				if (data->map->map[map_x][map_y] == 1)
					hit = 1;
			}

			//anti fisheye
			if (side == 0)
				perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / raydir_x;
			else
				perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / raydir_y;

			line_height = (int)(data->map->height_map / perp_wall_dist);
			draw_start = (line_height * -1) / 2 + data->map->height_map / 2;
			draw_end = line_height / 2 + data->map->height_map / 2;
			draw_start = (draw_start < 0) ? 0 : draw_start;
			draw_end = (draw_end >= data->map->height_map) ? data->map->height_map - 1 : draw_end;

			int color = 0x00FF0000;

			if (side == 1)
				color = color / 2;
			while (draw_start < draw_end)
			{
				ft_mlx_pixel_put(data->img->img, x, draw_start, color);
				draw_start++;
			}
			x++;
		}
		mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
	}
	return(1);
}
