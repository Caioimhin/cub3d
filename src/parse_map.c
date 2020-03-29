/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:17:38 by kparis            #+#    #+#             */
/*   Updated: 2020/03/29 01:44:10 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		not_wall(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	check_map_validity(t_mlx *data)
{
	int x;
	int y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			//premiere ligne
			if (y == 0 && (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
				error_message("wrong map");
			//premier char
			if (x == 0 && (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
				error_message("wrong map");
			//si c'est une case libre, ne doit pas être entourer d'espace
			if (not_wall(data->map->map[y][x]) == 1)
			{
				//case d'avant
				if (data->map->map[y][x - 1] == ' ')
					error_message("Wrong map");
				//case d'après
				if (data->map->map[y][x + 1] == ' ')
					error_message("Wrong map");
				//case au dessus si on est pas sur la premiere ligne
				if (data->map->map[y - 1][x] == ' ' && y != 0)
					error_message("Wrong map");
				//case en dessous si il y une ligne après existante
				if (data->map->map[y + 1])
					if (data->map->map[y + 1][x] == ' ')
						error_message("Wrong map");
			}
			//dernier char
			char last_char = data->map->map[y][ft_strlen(data->map->map[y]) - 1];
			if (last_char != '1' && last_char != ' ')
				error_message("Wrong map");
			//derniere ligne
			if (!data->map->map[y + 1])
				if (data->map->map[y][x] != '1' && data->map->map[y][x] != ' ')
					error_message("wrong map");
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'S' || data->map->map[y][x] == 'W' || data->map->map[y][x] == 'E')
			{
				data->map->pos_x = x;
				data->map->pos_y = y;
			}
			x++;
		}
		y++;
	}
}

void	parse_map(int fd, t_mlx *data)
{
	char *line;
	int map_start;

	map_start = 0;

	while (get_next_line(fd, &line))
	{
		if (map_start == 0 && (line[0] == '1' || line[0] == ' '))
			map_start = 1;
		if (map_start == 1 && (line[0] == '1' || line[0] == ' '))
			data->map->map = ft_realloc_char_tab(data->map->map, line);
		else if (map_start == 0)
			continue;
		else if (map_start == 1)
			map_start = 2;
		free(line);
	}
	free(line);
	close(fd);
	check_map_validity(data);
}
