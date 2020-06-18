/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:59:00 by kparis            #+#    #+#             */
/*   Updated: 2020/06/18 18:34:41 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture_img(t_ray *ray)
{
	t_img	*text_img;

	if (ray->side == 0)
	{
		if (ray->ray.x > 0)
			text_img = &ray->ea_img;
		else
			text_img = &ray->we_img;
	}
	else
	{
		if (ray->ray.y > 0)
			text_img = &ray->so_img;
		else
			text_img = &ray->no_img;
	}
	ray->text.x = (int)(ray->wall_x * (double)text_img->size.x);
	if (ray->side == 0 && ray->ray.x > 0)
		ray->text.x = text_img->size.x - ray->text.x - 1;
	if (ray->side == 1 && ray->ray.y < 0)
		ray->text.x = text_img->size.x - ray->text.x - 1;
	return (text_img);
}

void	get_texture(t_data *data, char *line, char *texture)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		close_program(data, "Failed allocating memory for path ", texture);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4) &&
		ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".png", 4))
		close_program(data, "Wrong extension for file ", texture);
	if (!ft_strncmp(texture, "NO", 2))
		data->maps.no_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "SO", 2))
		data->maps.so_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
		data->maps.we_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
		data->maps.ea_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S ", 2))
		data->maps.s_path = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	ft_putendl(texture);
}

void	test_path(t_data *data, char *path)
{
	int fd;

	if ((fd = open(path, O_RDWR | O_CREAT | O_TRUNC,
				S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		close_program(data, "Couldn't open all the textures path", "");
}
