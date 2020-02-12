/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/02/11 11:17:13 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"
#define RES_X_MAX 1920
#define	RES_Y_MAX 1080

typedef struct	s_img
{
	void		*img;
	void		*img_cpy;
	void		*adress;
	int			bits_per_pxl;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_map
{
	int		res_x;
	int		res_y;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		floor;
	int		ceiling;
	int		start;
	int		**map;
	int		player;
	int		width_map;
	int		height_map;
}				t_map;


typedef	struct	s_mlx {
	void		*mlx;
	void		*window;
	t_img		*img;
	t_map		*map;
}				t_mlx;

void			parser_cub(char *line, t_map *map);
int				close_cub(t_mlx *data);
int				handle_keypress(int keycode, t_mlx *data);
void			parse_map(t_map *map, int fd);