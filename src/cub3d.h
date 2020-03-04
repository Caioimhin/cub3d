/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/03/04 17:59:13 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../libft/libft.h"
#include "mlx.h"

#define RES_X_MAX 2560
#define	RES_Y_MAX 1440
#define RES_X_MIN 192
#define	RES_Y_MIN 108
#define	ESC 53
#define	UP 13
#define	DOWN 1
#define	LEFT 0
#define	RIGHT 2
#define TURN_LEFT 123
#define TURN_RIGHT 124

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

typedef	struct	s_key {
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			key_esc;
	int			key_turnleft;
	int			key_turnright;
}				t_key;

typedef	struct	s_player {
	double		rot_speed;
	int			player_x;
	int			player_y;
	int			player_dir_x;
	int			player_dir_y;
}				t_player;

typedef	struct	s_ray
{
	int			x;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			w;
	int			h;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	double		movespeed;
}				t_ray;

typedef	struct	s_mlx {
	void		*mlx;
	void		*window;
	t_img		*img;
	t_map		*map;
	t_key		*key;
	t_player	*player;
	t_ray		*ray;
}				t_mlx;

void			parser_cub(char *line, t_map *map);
int				close_cub(t_mlx *data);
int				handle_keypress(int keycode, t_mlx *data);
int				handle_keyrelease(int keycode, t_mlx *data);
void			parse_map(t_mlx *data, int fd);
void			get_img_adrr(t_mlx *data);
void			ft_mlx_pixel_put(t_img *img, int x, int y, int color);
