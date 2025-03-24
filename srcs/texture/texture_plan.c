/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:15:48 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 02:15:48 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Objects/Plane.h"
#include "../../includes/Raytracer.h"
#include "../../includes/macros.h"
#include <stdio.h>

static int get_color(int x, int y, t_img *texture)
{
	int	px_s;

	px_s = (y * texture->line_len + x * (texture->bpp / 8));
	return (get_rgb(texture->addr[px_s],
				 texture->addr[px_s + 1],
				 texture->addr[px_s + 2]));
}

t_co get_pl_texture_color(t_pl *pl, t_hit hit)
{
	float	uv[2];
	int		tex_x;
	int		tex_y;
	int		color;
	t_co	col;

	uv[0] = dot(vec_sub(hit.ori, pl->pt), pl->x);
	uv[1] = dot(vec_sub(hit.ori, pl->pt), pl->y);
	tex_x = (int)(fmod(uv[0]/TEX_SCALE_FACTOR, 1.0) * pl->tex.b.width);
	tex_y = (int)(fmod(uv[1]/TEX_SCALE_FACTOR, 1.0) * pl->tex.b.height);
	tex_x = (tex_x + pl->tex.b.width) % pl->tex.b.width;
	tex_y = (tex_y + pl->tex.b.height) % pl->tex.b.height;
	color = get_color(tex_x, tex_y, &pl->tex.b);
	col.r = (float)((color >> 16) & 0xFF) / 255.0f;
	col.g = (float)((color >> 8) & 0xFF) /255.0f;
	col.b = (float)((color) & 0xFF) / 255.0f;
	return (col);
}

t_v3	get_pl_nmap_vec(t_pl *pl, t_hit hit)
{
	float	uv[2];
	int		tex_x;
	int		tex_y;

	uv[0] = dot(vec_sub(hit.ori, pl->pt), pl->x);
	uv[1] = dot(vec_sub(hit.ori, pl->pt), pl->y);
	tex_x = (int)(fmod(uv[0]/TEX_SCALE_FACTOR, 1.0) * pl->tex.n.width);
	tex_y = (int)(fmod(uv[1]/TEX_SCALE_FACTOR, 1.0) * pl->tex.n.height);
	tex_x = (tex_x + pl->tex.n.width) % pl->tex.n.width;
	tex_y = (tex_y + pl->tex.n.height) % pl->tex.n.height;
	return (get_nmap_vec(&pl->tex.n, tex_x, tex_y, hit.norm));
}
