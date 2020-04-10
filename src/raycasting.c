/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 17:35:56 by kparis            #+#    #+#             */
/*   Updated: 2020/04/10 04:40:09 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_mlx *data, t_ray *ray)
{
	int x;

	x = 0;
	if (!ray->init)
		init_ray(data, ray);

	while (x < data->map->res_x)
	{
		//calculate ray position and direction
		ray->camera_x = 2 * x / (double)data->map->res_x - 1; //x-coordinate in camera space
		ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		//which box of the map we're in
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;

		//length of ray from one x or y-side to next x or y-side
		ray->deltadist_x = (ray->raydir_y == 0) ? 0 : ((ray->raydir_x == 0) ? 1 : fabs(1 / ray->raydir_x));
		ray->deltadist_y = (ray->raydir_x == 0) ? 0 : ((ray->raydir_y == 0) ? 1 : fabs(1 / ray->raydir_y));
		ray->hit = 0; //was there a wall ray->hit?
		//calculate step and initial sideDist
		if(ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->deltadist_x;
		}
		if(ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->deltadist_y;
		}
		dda(data, ray);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;

		//Calculate height of line to draw on screen
		ray->line_height = abs((int)(data->map->res_y / ray->perp_wall_dist));

		//calculate lowest and highest pixel to fill in current stripe
		ray->draw_start = -ray->line_height / 2 + data->map->res_y / 2;
		if(ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + data->map->res_y / 2;
		if (ray->draw_end >= data->map->res_y)
			ray->draw_end = data->map->res_y - 1;

		t_img texture;

		if (ray->side == 0)
		{
			if (ray->raydir_x < 0)
				create_texture_img(data, data->map->w_path, &texture);
			else
				create_texture_img(data, data->map->e_path, &texture);//est
		}
		else if (ray->side == 1)
		{
			if (ray->raydir_y < 0)
				create_texture_img(data, data->map->n_path, &texture);//nord
			else
				create_texture_img(data, data->map->s_path, &texture);//sud
		}
		// a modifier //

		frame->text.x = (int)(frame->wall_x * (double)text_img->size.x);
		if(frame->side == 0 && frame->ray.x > 0)
			frame->text.x = text_img->size.x - frame->text.x;
		if(frame->side == 1 && frame->ray.y < 0)
			frame->text.x = text_img->size.x - frame->text.x;
		//fin de la partie a modifier //







		// while (ray->draw_start < ray->draw_end)
		// {
		// 	ft_mlx_pixel_put(data->img, x, ray->draw_start, color);
		// 	ray->draw_start++;
		// }
		//ceiling and floor
		// if (ray->draw_end < 0)
		// {
		// 	ray->draw_end = data->map->res_y;
		// }
		// ray->draw_start=ray->draw_end;
		// while (ray->draw_start < data->map->res_y)
		// {
		// 	ft_mlx_pixel_put(data->img, x, ray->draw_start, 0x00505560);// trace le pixel du sol
		// 	ft_mlx_pixel_put(data->img, x, data->map->res_y - ray->draw_start - 1 ,0x00FFE441);// trace le pixel du plafond
		// 	ray->draw_start++;
		// }
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
}

int		loop(t_mlx *data)
{
	if (data->k_down || data->k_up || data->k_left ||
		data->k_right || data->k_turn_left || data->k_turn_right)
	{
		clear(data);
		move(data, data->ray);
		raycasting(data, data->ray);
	}
	return (EXIT_SUCCESS);
}