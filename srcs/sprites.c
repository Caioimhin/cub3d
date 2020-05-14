/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:48 by kparis            #+#    #+#             */
/*   Updated: 2020/05/14 23:54:44 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	void
draw_sprite_column(t_data *data, t_ray *F, t_img *img, int stripe)
{
	t_int		spr_img_pos;
	t_maps	*S;
	int			d;

	spr_img_pos.x = stripe;
	spr_img_pos.y = F->spr_draw_start.y;
	S = &data->maps;
	F->text.x = (int)(256 * fabs(stripe - (-F->spr_size.x / 2
		+ F->spr_screen_x)) * img->size.x / F->spr_size.x) / 256;
	if (F->spr_inv.y > 0 && stripe >= 0 && stripe < S->win_size.x
		&& F->spr_inv.y < F->z_buffer[stripe])
	{
		while (spr_img_pos.y < F->spr_draw_end.y)
		{
			d = (spr_img_pos.y)
				* 256 - S->win_size.y * 128 + F->spr_size.y * 128;
			F->text.y = ((d * img->size.y) / F->spr_size.y) / 256;
			if ((img->colors
				[(img->size.y * F->text.y + F->text.x)] & 0x00FFFFFF) != 0)
				put_pixel(&data->img, spr_img_pos,
					img->colors[(img->size.y * F->text.y + F->text.x)]);
			spr_img_pos.y++;
		}
	}
}

	void
set_sprite_drawing_limits(t_maps *S, t_ray *F, int i)
{
	double	inv;
	t_coord	spr_diff;

	spr_diff.x = S->spr_x[i] - F->pos.x;
	spr_diff.y = S->spr_y[i] - F->pos.y;
	inv = 1.0 / (F->plane.x * F->dir.y - F->dir.x * F->plane.y);
	F->spr_inv.x = inv * (F->dir.y * spr_diff.x - F->dir.x * spr_diff.y);
	F->spr_inv.y = inv * (F->plane.x * spr_diff.y - F->plane.y * spr_diff.x);
	F->spr_screen_x = ((S->win_size.x / 2) * (1 + F->spr_inv.x / F->spr_inv.y));
	F->spr_size.y = abs((int)(S->win_size.y / (F->spr_inv.y)));
	F->spr_draw_start.y = -F->spr_size.y / 2 + S->win_size.y / 2;
	if(F->spr_draw_start.y < 0)
		F->spr_draw_start.y = 0;
	F->spr_draw_end.y = F->spr_size.y / 2 + S->win_size.y / 2;
	if(F->spr_draw_end.y >= S->win_size.y)
		F->spr_draw_end.y = S->win_size.y;
	F->spr_size.x = abs((int)(S->win_size.y / (F->spr_inv.y)));
	F->spr_draw_start.x = -F->spr_size.x / 2 + F->spr_screen_x - 1;
	if(F->spr_draw_start.x < 0)
		F->spr_draw_start.x = 0;
	F->spr_draw_end.x = F->spr_size.x / 2 + F->spr_screen_x + 1;
	if(F->spr_draw_end.x > S->win_size.x)
		F->spr_draw_end.x = S->win_size.x;
}

	void
draw_sprites(t_data *data, t_maps *S, t_ray *F, t_img *text)
{
	int	i;
	int	j;
	int	stripe;

	i = 0;
	j = 0;
	while (i < S->spr_count || j < S->spr_count)
	{
		if (j == F->spr_order[i] && F->spr_dist[i] > 0.1)
		{
			set_sprite_drawing_limits(S, F, i);
			stripe = F->spr_draw_start.x;
			while (stripe < F->spr_draw_end.x)
			{
				draw_sprite_column(data, F, text, stripe);
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
	}
}

	void
init_sprite_order(t_maps *S, t_ray *F)
{
	int i;

	i = 0;
	while (i < S->spr_count && !F->spr_sorted)
	{
		F->spr_order[i] = i;
		F->spr_dist[i] =
			((F->pos.x - S->spr_x[i]) * (F->pos.x - S->spr_x[i])
			+ (F->pos.y - S->spr_y[i]) * (F->pos.y - S->spr_y[i]));
		i++;
	}
}

	void
sort_sprites(t_maps *maps, t_ray *F)
{
	t_int	at;
	int		tmp_order;

	init_sprite_order(maps, F);
	at.x = 0;
	while (at.x < maps->spr_count - 1)
	{
		at.z = 0;
		at.y = at.x;
		while (++at.y < maps->spr_count)
		{
			if ((F->spr_dist[at.x] < F->spr_dist[at.y]
				&& F->spr_order[at.x] < F->spr_order[at.y])
				|| (F->spr_dist[at.x] > F->spr_dist[at.y]
				&& F->spr_order[at.x] > F->spr_order[at.y]))
			{
				at.z++;
				tmp_order = F->spr_order[at.x];
				F->spr_order[at.x] = F->spr_order[at.y];
				F->spr_order[at.y] = tmp_order;
			}
		}
		at.x = (at.z == 0) ? at.x + 1 : at.x;
	}
	F->spr_sorted++;
}
