/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:07 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:42:23 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_ray *ray, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = ray->pos.x;
	pos.y = ray->pos.y;
	if (map[(int)pos.y][(int)(pos.x + ray->dir.x * move_speed)] == '0')
		ray->pos.x += ray->dir.x * move_speed;
	if (map[(int)(pos.y + ray->dir.y * move_speed)][(int)pos.x] == '0')
		ray->pos.y += ray->dir.y * move_speed;
}

void	move_backward(t_ray *ray, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = ray->pos.x;
	pos.y = ray->pos.y;
	if (map[(int)pos.y][(int)(pos.x - ray->dir.x * move_speed)] == '0')
		ray->pos.x -= ray->dir.x * move_speed;
	if (map[(int)(pos.y - ray->dir.y * move_speed)][(int)pos.x] == '0')
		ray->pos.y -= ray->dir.y * move_speed;
}

void	move_right(t_ray *ray, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = ray->pos.x;
	pos.y = ray->pos.y;
	if (map[(int)pos.y][(int)(pos.x - ray->dir.y * move_speed)] == '0')
		ray->pos.x -= ray->dir.y * move_speed;
	if (map[(int)(pos.y + ray->dir.x * move_speed)][(int)pos.x] == '0')
		ray->pos.y += ray->dir.x * move_speed;
}

void	move_left(t_ray *ray, char **map)
{
	double	move_speed;
	t_coord	pos;

	move_speed = 0.33;
	pos.x = ray->pos.x;
	pos.y = ray->pos.y;
	if (map[(int)pos.y][(int)(pos.x + ray->dir.y * move_speed)] == '0')
		ray->pos.x += ray->dir.y * move_speed;
	if (map[(int)(pos.y - ray->dir.x * move_speed)][(int)pos.x] == '0')
		ray->pos.y -= ray->dir.x * move_speed;
}
