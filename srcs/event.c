/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:17 by kparis            #+#    #+#             */
/*   Updated: 2020/06/03 01:05:35 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;
	t_coord	*plane;

	rot_speed = 0.18;
	plane = &ray->plane;
	old_dir_x = ray->dir.x;
	ray->dir.x = old_dir_x * cos(-rot_speed) - ray->dir.y * sin(-rot_speed);
	ray->dir.y = old_dir_x * sin(-rot_speed) + ray->dir.y * cos(-rot_speed);
	old_plane_x = ray->plane.x;
	plane->x = old_plane_x * cos(-rot_speed) - ray->plane.y * sin(-rot_speed);
	plane->y = old_plane_x * sin(-rot_speed) + ray->plane.y * cos(-rot_speed);
}

void	look_right(t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;
	t_coord	*plane;

	rot_speed = 0.18;
	plane = &ray->plane;
	old_dir_x = ray->dir.x;
	ray->dir.x = old_dir_x * cos(rot_speed) - ray->dir.y * sin(rot_speed);
	ray->dir.y = old_dir_x * sin(rot_speed) + ray->dir.y * cos(rot_speed);
	old_plane_x = ray->plane.x;
	plane->x = old_plane_x * cos(rot_speed) - ray->plane.y * sin(rot_speed);
	plane->y = old_plane_x * sin(rot_speed) + ray->plane.y * cos(rot_speed);
}

int		press_key(int key, t_data *data)
{
	if (key == KEY_ESC)
		close_program(data, "\nEverything went well ! ", "\n");
	if (key == KEY_LEFT)
		look_left(&data->ray);
	if (key == KEY_RIGHT)
		look_right(&data->ray);
	if (key == KEY_Z)
		move_forward(&data->ray, data->maps.map);
	if (key == KEY_S)
		move_backward(&data->ray, data->maps.map);
	if (key == KEY_D)
		move_right(&data->ray, data->maps.map);
	if (key == KEY_Q)
		move_left(&data->ray, data->maps.map);
	data->ray.spr_sorted = 0;
	return (key);
}

int		cross_press(t_data *data)
{
	close_program(data, "\nEverything went well ! ", "\\o/\n");
	return (0);
}

void	hook_event(t_data *data)
{
	mlx_hook(data->window, 2, 1L << 0, press_key, data);
	mlx_hook(data->window, 17, 1L << 17, cross_press, data);
	return ;
}
