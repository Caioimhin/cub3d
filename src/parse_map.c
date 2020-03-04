/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:10 by kparis            #+#    #+#             */
/*   Updated: 2020/03/04 18:06:55 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_map()
{
	ft_putendl("Error\nInvalid map");
	exit(EXIT_FAILURE);
}

void	get_dir(char c, t_mlx *data)
{
	if (c == 'N')
	{
		data->player->player_dir_x = -1;
		data->player->player_dir_y = 0;
	}
	else if (c == 'S')
	{
		data->player->player_dir_x = 0;
		data->player->player_dir_y = 0;
	}
	else if (c == 'E')
	{
		data->player->player_dir_x = 1;
		data->player->player_dir_y = 0;
	}
	else if (c == 'W')
	{
		data->player->player_dir_x = 0;
		data->player->player_dir_y = -1;
	}
}

int		normal_case(int j, int i, char *line, t_mlx *data)
{
	int x;

	x = 0;
	while (i < (int)ft_strlen(line))
	{
		while (!ft_isdigit(line[i]) && (line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E'))
			i += 1;
		if ((line[i] == '0' || line[i] == '1' || line[i] == '2') && line[0] == '1')
		{
			data->map->map[j] = ft_realloc_int(data->map->map[j], x, ft_atoi(&line[i]));
			i += 1;
			x += 1;
		}
		else
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
				line[i] == 'W') && data->map->player == 0)
			{
				data->map->map[j] = ft_realloc_int(data->map->map[j], x, 0);
				data->player->player_x = x;
				data->player->player_y = j;
				get_dir(line[i], data);
				i += 1;
				x += 1;
				data->map->player = 1;
				continue;
			}
			else
				wrong_map();
		}
	}
	(data->map->map[j][data->map->width_map - 1] != 1) ? wrong_map() : 0;
	j += 1;
	return (j);
}

int		map_start(int j, int i, char *line, t_mlx *data)
{
	int x;

	x = 0;
	while (i < (int)ft_strlen(line))
	{
		while (!ft_isdigit(line[i]))
			i += 1;
		if (line[i] != '1')
		{
			ft_putendl("Error\nInvalid map");
			exit(EXIT_FAILURE);
		}
		data->map->map[j] = ft_realloc_int(data->map->map[j], x, ft_atoi(&line[i]));
		i += 1;
		x += 1;
		data->map->width_map = x;
	}
	data->map->start = 1;
	j += 1;
	return (j);
}

void	parse_map(t_mlx *data, int fd)
{
	char *line;
	int i;
	int j;

	line = 0;
	data->map->start = 0;
	data->map->player = 0;
	data->map->map = malloc(sizeof(int*) * 500);
	j = 0;
	while(get_next_line(fd, &line))
	{
		parser_cub(line,data->map);
		i = 0;
		if (line[0] == '1')
		{
			if (data->map->start == 0)
				j = map_start(j, i, line, data);
			else
				j = normal_case(j, i, line, data);
		}
	}
	i = 0;
	data->map->height_map = map_start(j, i, line, data);

}
