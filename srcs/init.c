/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:52 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:39:03 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_settings(t_maps *maps)
{
	maps->win_size.x = 0;
	maps->win_size.y = 0;
	maps->NO_path = NULL;
	maps->SO_path = NULL;
	maps->WE_path = NULL;
	maps->EA_path = NULL;
	maps->S_path = NULL;
	maps->floor_color = -1;
	maps->ceiling_color = -1;
	maps->map = NULL;
	maps->map_size.x = 1;
	maps->map_size.y = 0;
	maps->player_orientation = (char)NULL;
	maps->starting_pos.x = -1;
	maps->starting_pos.y = -1;
	maps->spr_count = 0;
	maps->spr_x = NULL;
	maps->spr_y = NULL;
	maps->spr_text = NULL;
	maps->done = 0;
}

void	init_dir_and_plane(t_maps *maps, t_ray *ray)
{
	ray->dir.x = 0;
	ray->dir.y = -1;
	ray->plane.x = 0.7;
	ray->plane.y = 0;
	if (maps->player_orientation == 'E')
	{
		ray->dir.x = 1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = 0.7;
	}
	if (maps->player_orientation == 'S')
	{
		ray->dir.x = 0;
		ray->dir.y = 1;
		ray->plane.x = -0.7;
		ray->plane.y = 0;
	}
	if (maps->player_orientation == 'W')
	{
		ray->dir.x = -1;
		ray->dir.y = 0;
		ray->plane.x = 0;
		ray->plane.y = -0.7;
	}
}

void	init_sprites(t_data *data, t_maps *maps, t_ray *ray)
{
	if (!(maps->spr_x = malloc(sizeof(double *) * (maps->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_x", "");
	if (!(maps->spr_y = malloc(sizeof(double *) * (maps->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_y", "");
	if (!(maps->spr_text = malloc(sizeof(char *) * (maps->spr_count))))
		close_program(data, "Couldn't allocate mem for spr_text", "");
	if (!(ray->z_buffer = malloc(sizeof(double *) * maps->win_size.x)))
		close_program(data, "Failed allocating z_buffer", "");
	if (!(ray->spr_order = malloc(sizeof(int *) * maps->spr_count)))
		close_program(data, "Failed allocating spr_order", "");
	if (!(ray->spr_dist = malloc(sizeof(double *) * maps->spr_count)))
		close_program(data, "Failed allocating spr_dist", "");
}

void	init_frame(t_data *data, t_maps *maps, t_ray *ray)
{
	init_dir_and_plane(maps, ray);
	ray->pos.x = maps->starting_pos.x + 0.5;
	ray->pos.y = maps->starting_pos.y + 0.5;
	maps->map[maps->starting_pos.y][maps->starting_pos.x] = '0';
	ray->spr_sorted = 0;
	create_texture_img(data, maps->NO_path, &ray->NO_img);
	create_texture_img(data, maps->SO_path, &ray->SO_img);
	create_texture_img(data, maps->WE_path, &ray->WE_img);
	create_texture_img(data, maps->EA_path, &ray->EA_img);
	create_texture_img(data, maps->S_path, &ray->S_img);
}

void	init_data(t_data *data)
{
	t_int	win_size;
	t_img	*img;

	win_size.x = data->maps.win_size.x;
	win_size.y = data->maps.win_size.y;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, win_size.x, win_size.y, "Cub3D");
	img = &data->img;
	img->ptr = mlx_new_image(data->mlx, data->maps.win_size.x,
			data->maps.win_size.y);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	img->size.x = data->maps.win_size.x;
	img->size.y = data->maps.win_size.y;
	init_frame(data, &data->maps, &data->ray);
}
