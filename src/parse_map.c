/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:10 by kparis            #+#    #+#             */
/*   Updated: 2020/02/10 16:25:03 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		normal_case(int j, int i, char *line, t_map *map)
{
	while (i < (int)ft_strlen(line))
	{
		if (ft_atoi(&line[i]) != 0 && ft_atoi(&line[i]) != 1 && ft_atoi(&line[i]) != 2 && line[0] != '1' && line[ft_strlen(line) - 1] != '1')
		{
			if ((&line[i] == 'N' || &line[i] == 'S' || &line[i] == 'E' || &line[i] == 'W') && map->player == 0)
				map->player == 1;
			else
			{
				ft_putendl("Error\nInvalid map");
				exit(EXIT_FAILURE);
			}

		}
		i++;
	}
	map->map[j] = line;
	j++;
	return (j);
}

int		map_start(int j, int i, char *line, t_map *map)
{
	while (i < (int)ft_strlen(line))
	{
		if (ft_atoi(&line[i]) != 1)
		{
			ft_putendl("Error\nInvalid map");
			exit(EXIT_FAILURE);
		}
		i += 1;
	}
	map->map[j] = line;
	map->start = 1;
	j++;
	return (j);
}

//parser et vérifier la maps
void	parse_map(t_map *map, int fd)
{
	char *line;
	int i;
	int j;

	line = 0;
	map->start = 0;
	map->player = 0;
	map->map = malloc(sizeof(char*) * 500);
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
	j = map_start(j, i, line, map);
	map->map[j] = 0;
}