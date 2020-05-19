/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:59 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:41:23 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_map(t_data *data, t_maps *maps, int x, int y)
{
	char c;

	c = maps->map[y][x];
	if (c == ' ')
		return (1);
	if (c == '1')
		return (2);
	if (c == '2')
		return (3);
	if (c == '0')
		return (3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (maps->player_orientation == (char)NULL)
		{
			maps->player_orientation = c;
			maps->starting_pos.x = x;
			maps->starting_pos.y = y;
		}
		else if (x != maps->starting_pos.x || y != maps->starting_pos.y)
			close_program(data, "More than one player set", "");
		return (4);
	}
	return (0);
}

int		check_map_errors(t_data *data, t_maps *maps)
{
	int x;
	int y;

	y = 0;
	while (y < maps->map_size.y)
	{
		x = 0;
		while (x < (int)ft_strlen(maps->map[y]))
		{
			if ((y == 0 || y == (maps->map_size.y - 1))
				&& is_map(data, maps, x, y) > 2)
				close_program(data, "Map not closed at top or bottom", "");
			if (!is_map(data, maps, x, y))
				close_program(data, "Wrong object in map", "");
			if (is_map(data, maps, x, y) >= 3)
				check_square_neighbors(data, maps, x, y);
			x++;
		}
		y++;
	}
	if (maps->player_orientation == (char)NULL)
		close_program(data, "No map or no player set :'(", "");
	return (0);
}

void	check_square_neighbors(t_data *data, t_maps *maps, int x, int y)
{
	int i;
	int j;

	if (maps->map[y][x] >= '2' && maps->map[y][x] <= '9')
		maps->spr_count++;
	i = x - 1;
	while (i <= x + 1)
	{
		j = y - 1;
		while (j <= y + 1)
		{
			if (maps->map[j][i] == '\0' || maps->map[j][i] == ' ')
				close_program(data, "Map not closed", "");
			if (!is_map(data, maps, i, j))
				close_program(data, "Wrong object in map", "");
			j++;
		}
		i++;
	}
}

/*
** NB : map_size.y has not yet been incremented in fill_tmp hence +1 each time
*/

char	**get_tmp_map(t_data *data, t_maps *maps, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char**) * (maps->map_size.y + 1))))
		close_program(data, "Failed allocating memory for tmp map\n", "");
	while (i < maps->map_size.y + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char*) * (maps->map_size.x + 1))))
			close_program(data, "Failed allocating memory for tmp map\n", "");
		if (i != (maps->map_size.y))
			tmp[i] =
				ft_strcharcpy(tmp[i], maps->map[i], maps->map_size.x, ' ');
		else
			tmp[i] = ft_strcharcpy(tmp[i], line, maps->map_size.x, ' ');
		i++;
	}
	return (tmp);
}

void	get_map(t_data *data, char *line, int i, t_maps *maps)
{
	char	**tmp;

	if (maps->map_size.x < (int)ft_strlen(line))
		maps->map_size.x = ft_strlen(line);
	i = 0;
	tmp = NULL;
	tmp = get_tmp_map(data, maps, tmp, line);
	free_map(maps);
	maps->map_size.y = maps->map_size.y + 1;
	i = 0;
	if (!(maps->map = malloc(sizeof(char**) * maps->map_size.y)))
		close_program(data, "Failed allocating memory for map\n", "");
	while (i < maps->map_size.y)
	{
		if (!(maps->map[i] = malloc(sizeof(char*) * maps->map_size.x)))
			close_program(data, "Failed allocating memory for map\n", "");
		maps->map[i] =
			ft_strcharcpy(maps->map[i], tmp[i], maps->map_size.x, ' ');
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
}
