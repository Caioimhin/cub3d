/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:30:45 by kparis            #+#    #+#             */
/*   Updated: 2020/02/14 16:41:22 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int raycasting(t_mlx *data)
{
	//pts de départ de la cam
	double pos_x = 26, pos_y = 11;
	//direction ou regarde la cam
	double dir_x = 0, dir_y = 1;
	//vecteur plan de projection : ???
	double plane_x = 0, plane_y = 1;
	int x = 0;
	int y = 0;

	double cam_x;
	double ray_pos_x;
	double ray_pos_y;
	double ray_dir_x;
	double ray_dir_y;

	//dda
	int map_x;
	int map_y;

	double side_dist_x;
	double side_dist_y;

	double delta_dist_x;
	double delta_dist_y;

	int step_x;
	int step_y;
	int hit;
	int side;

	double real_wall_dist = 0;

	//trouver la hauteur de la colone a tracer
	int	line_height;
	int draw_start;
	int draw_end;

	int color;

	if (data->key->key_up || data->key->key_down || data->key->key_left || data->key->key_right || data->player->rot_speed)
	{
		while (x <= data->map->res_x)
		{
			cam_x = (2 * x / data->map->res_x)-1;
			ray_pos_x = pos_x;
			ray_pos_y = pos_y;
			ray_dir_x = dir_x + plane_x * cam_x;
			ray_dir_y = dir_y + plane_y * cam_x;

			//dda

			map_x = (int)ray_pos_x;
			map_y = (int)ray_pos_y;

			delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
			delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));

			hit = 0;

			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (ray_pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1 - ray_pos_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (ray_pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1 - ray_pos_y) * delta_dist_y;
			}
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
				if (data->map->map[map_y][map_x] > 0)
					hit = 1;
			}
			//correction optique ici
			if (side == 0)
				real_wall_dist = fabs((map_x - ray_pos_x + (1 - step_x) / 2) / ray_dir_x);
			else
				real_wall_dist = fabs((map_y - ray_pos_y + (1 - step_y) / 2) / ray_dir_y);
			//trouver la hauteur de la colone a tracer
			line_height = abs(data->map->res_y / (int)real_wall_dist);
			draw_start = (int)-line_height / 2 + data->map->res_y / 2;
			draw_end = (int)line_height / 2 + data->map->res_y / 2;
			if (draw_start < 0)
				draw_start = 0;
			if (draw_end >= data->map->res_y)
				draw_end = data->map->res_y - 1;
			//tracer
			(side == 0) ? color = 0x00f2f2f2 : 0x00CCCCCC;
			while (y < draw_end)
			{
				ft_mlx_pixel_put(data->img, (int)x, (int)y, color);
				y += 1;
			}
			x++;
		}
		mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
	}
	return(1);
}
