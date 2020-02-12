/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:10 by kparis            #+#    #+#             */
/*   Updated: 2020/02/11 14:28:31 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_map()
{
	ft_putendl("Error\nInvalid map");
	exit(EXIT_FAILURE);
}

int		normal_case(int j, int i, char *line, t_map *map)
{
	int x;

	x = 0;
	while (i < (int)ft_strlen(line))
	{
		while (!ft_isdigit(line[i]) && line[i] != 'N')
			i += 1;
		if ((line[i] == '0' || line[i] == '1' || line[i] == '2') && line[0] == '1')
		{
			map->map[j] = ft_realloc_int(map->map[j], x, ft_atoi(&line[i]));
			i += 1;
			x += 1;
		}
		else
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
				line[i] == 'W') && map->player == 0)
			{
				map->map[j] = ft_realloc_int(map->map[j], x, line[i]);
				i += 1;
				x += 1;
				continue;
			}
			else
				wrong_map();
		}
	}
	(map->map[j][map->width_map - 1] != 1) ? wrong_map() : 0;
	j += 1;
	return (j);
}

int		map_start(int j, int i, char *line, t_map *map)
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
		map->map[j] = ft_realloc_int(map->map[j], x, ft_atoi(&line[i]));
		i += 1;
		x += 1;
		map->width_map = x;
	}
	map->start = 1;
	j += 1;
	return (j);
}

void	parse_map(t_map *map, int fd)
{
	char *line;
	int i;
	int j;

	line = 0;
	map->start = 0;
	map->player = 0;
	map->map = malloc(sizeof(int*) * 500);
	j = 0;
	while(get_next_line(fd, &line))
	{
		parser_cub(line, map);
		i = 0;
		if (line[0] == '1')
		{
			if (map->start == 0)
				j = map_start(j, i, line, map);
			else
				j = normal_case(j, i, line, map);
		}
	}
	i = 0;
	map->height_map = map_start(j, i, line, map);

}