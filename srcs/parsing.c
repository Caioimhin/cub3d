/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:17 by kparis            #+#    #+#             */
/*   Updated: 2020/06/16 15:38:39 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		settings_ok(t_data *data, t_maps *maps, char *line)
{
	if ((!ft_memcmp(line, "R ", 2) && maps->win_size.y) ||
		(!ft_memcmp(line, "NO ", 3) && maps->no_path) ||
		(!ft_memcmp(line, "SO ", 3) && maps->so_path) ||
		(!ft_memcmp(line, "EA ", 3) && maps->ea_path) ||
		(!ft_memcmp(line, "WE ", 3) && maps->we_path) ||
		(!ft_memcmp(line, "S ", 2) && maps->s_path) ||
		(!ft_memcmp(line, "F ", 2) && maps->floor_color > -1) ||
		(!ft_memcmp(line, "C ", 2) && maps->ceiling_color > -1))
		close_program(data, "One parameter is set twice\n", "");
	if (maps->win_size.x == -1 || maps->win_size.y == -1 ||
		maps->so_path == NULL || maps->we_path == NULL ||
		maps->ea_path == NULL || maps->no_path == NULL ||
		maps->s_path == NULL || maps->floor_color == -1 ||
		maps->ceiling_color == -1)
		return (0);
	else
		return (1);
}

int		check_settings(t_data *data, t_maps *maps, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && maps->map_size.y)
		close_program(data, "Empty line in map", "");
	else if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && !settings_ok(data, maps, &line[i]))
		close_program(data, "Parameter missing before map\n", "");
	else if (line[i] != '1' && settings_ok(data, maps, &line[i]))
		close_program(data, "Map not closed or invalid element\n", "");
	else if (line[i] != '1' && !settings_ok(data, maps, &line[i])
		&& !(!ft_memcmp(&line[i], "R ", 2) || !ft_memcmp(&line[i], "NO ", 3)
		|| !ft_memcmp(&line[i], "SO ", 3) || !ft_memcmp(&line[i], "WE ", 3)
		|| !ft_memcmp(&line[i], "EA ", 3) || !ft_memcmp(&line[i], "S ", 2)
		|| !ft_memcmp(&line[i], "F ", 2) || !ft_memcmp(&line[i], "C ", 2)))
		close_program(data, "Invalid parameter before map\n", "");
	return (i);
}

void	parse_line(t_data *data, char *line)
{
	int i;

	if ((i = check_settings(data, &data->maps, line)) == -1)
		return ;
	if (line[i] == 'R')
		get_resolution(data, &line[i], &data->maps);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture(data, &line[i], "NO");
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture(data, &line[i], "SO");
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture(data, &line[i], "WE");
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture(data, &line[i], "EA");
	if (line[i] == 'S' && line[i + 1] == ' ')
		get_texture(data, &line[i], "S ");
	if (line[i] == 'F' && line[i + 1] == ' ')
		get_color(data, &line[i], "F ");
	if (line[i] == 'C' && line[i + 1] == ' ')
		get_color(data, &line[i], "C ");
	if (line[i] == '1')
		get_map(data, line, i, &data->maps);
}

void	get_sprites_data(t_data *data, t_maps *maps, char **map)
{
	t_int	pos;
	int		i;

	pos.y = 1;
	i = 0;
	init_sprites(data, maps, &data->ray);
	while (pos.y < maps->map_size.y - 1 && i < maps->spr_count)
	{
		pos.x = 0;
		while (pos.x < maps->map_size.x && i < maps->spr_count)
		{
			if (map[pos.y][pos.x] == '2')
			{
				maps->spr_x[i] = pos.x + 0.5;
				maps->spr_y[i] = pos.y + 0.5;
				maps->spr_text[i] = map[pos.y][pos.x];
				i++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	parse_cub_file(t_data *data)
{
	int		ret;
	char	*line;

	line = NULL;
	init_settings(&data->maps);
	while ((ret = get_next_line(data->maps.fd, &line)) > 0)
	{
		parse_line(data, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	check_map_errors(data, &data->maps);
	get_sprites_data(data, &data->maps, data->maps.map);
	if ((close(data->maps.fd)) < 0)
		close_program(data, "Couldn't close .cub file", "");
	data->maps.done = 1;
}
