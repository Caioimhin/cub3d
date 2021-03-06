/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:43:42 by kparis            #+#    #+#             */
/*   Updated: 2020/06/25 13:01:36 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"
# define KEY_Q 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Z 13
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct	s_coord{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct	s_int{
	int			x;
	int			y;
	int			z;
}				t_int;

typedef struct	s_img{
	void		*ptr;
	int			*colors;
	int			bpp;
	int			line_length;
	int			endian;
	t_int		size;
}				t_img;

typedef struct	s_settings{
	int			fd;
	t_int		win_size;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*s_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	t_int		map_size;
	char		player_orientation;
	t_int		starting_pos;
	int			spr_count;
	double		*spr_x;
	double		*spr_y;
	char		*spr_text;
	int			done;
}				t_maps;

typedef struct	s_ray {
	t_coord		pos;
	t_coord		dir;
	t_coord		ray;
	t_coord		plane;
	double		camera_x;
	t_coord		map;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		perp_wall_dist;
	t_int		step;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_img		no_img;
	t_img		so_img;
	t_img		ea_img;
	t_img		we_img;
	t_img		s_img;
	t_int		text;
	double		*z_buffer;
	int			*spr_order;
	double		*spr_dist;
	t_coord		spr_inv;
	double		spr_screen_x;
	t_int		spr_size;
	t_int		spr_draw_start;
	t_int		spr_draw_end;
	int			spr_sorted;
}				t_ray;

typedef struct	s_data{
	void		*mlx;
	void		*window;
	t_img		img;
	t_maps		maps;
	t_ray		ray;
	int			save;
}				t_data;

/*
** cub3d.c
*/
void			check_args_errors(t_data *data, int argc, char **argv);
int				main(int argc, char **argv);
void			wrong_args(char *msg);

/*
** bmp.c
*/
unsigned char	*create_bmp_info_header(t_img *img);
unsigned char	*create_bmp_file_header(t_img *img, int padding_size);
void			fill_bmp(t_data *data, unsigned char *image,
	t_img *img, int bmp_fd);
char			*get_screenshot_path(t_data *data, char *path);
void			create_bmp(t_data *data, t_img *img, char *path);

/*
** colors.c
*/
unsigned char	*int_to_rgb(unsigned char *image, int color);
void			get_color(t_data *data, char *line, char *color);

/*
** event.c
*/
void			look_left(t_ray *ray);
void			look_right(t_ray *ray);
int				press_key(int key, t_data *data);
int				cross_press(t_data *data);
void			hook_event(t_data *data);

/*
** exit.c
*/
int				close_program(t_data *data, char *error_msg, char *str);
void			free_frame(t_data *data, t_ray *ray);
void			free_settings(t_maps *maps);
void			free_map(t_maps *maps);

/*
** ray.c
*/
int				render_next_ray(t_data *data);
void			perform_dda(t_data *data, t_ray *ray);
void			set_ray(t_data *data, t_ray *ray, int x);
void			set_drawing_limits(t_data *data, t_ray *ray);
void			draw_column(t_data *data, t_ray *ray, t_img *textimg, int x);

/*
** img.c
*/
void			put_pixel(t_img *img, t_int pos, int color);
void			create_texture_img(t_data *data, char *path, t_img *textimg);

/*
** init.c
*/
void			init_settings(t_maps *maps);
void			init_dir_and_plane(t_maps *maps, t_ray *ray);
void			init_sprites(t_data *data, t_maps *maps, t_ray *ray);
void			init_ray(t_data *data, t_maps *maps, t_ray *ray);
void			init_data(t_data *data);

/*
** map.c
*/
int				is_map(t_data *data, t_maps *maps, int i, int j);
int				check_map_errors(t_data *data, t_maps *maps);
void			check_around(t_data *data, t_maps *maps,
	int i, int j);
char			**get_tmp_map(t_data *data, t_maps *maps,
	char **tmp, char *line);
void			get_map(t_data *data, char *line, int i, t_maps *maps);

/*
 ** move.c
*/
void			move_forward(t_ray *ray, char **map);
void			move_backward(t_ray *ray, char **map);
void			move_right(t_ray *ray, char **map);
void			move_left(t_ray *ray, char **map);

/*
** parsing.c
*/
int				settings_ok(t_data *data, t_maps *maps, char *line);
int				check_settings(t_data *data, t_maps *maps, char *line);
void			parse_line(t_data *data, char *line);
void			get_sprites_data(t_data *data, t_maps *maps, char **map);
void			parse_cub_file(t_data *data);

/*
** resolution.c
*/
void			get_resolution(t_data *data, char *line, t_maps *maps);

/*
** sprites.c
*/
void			draw_sprites(t_data *data, t_maps *maps,
	t_ray *ray, t_img *textimg);
void			init_sprite_order(t_maps *maps, t_ray *ray);
void			sort_sprites(t_maps *maps, t_ray *ray);

/*
** textures.c
*/
t_img			*get_texture_img(t_ray *ray);
void			get_texture(t_data *data, char *line, char *texture);
void			test_path(t_data *data, char *texture);
#endif
