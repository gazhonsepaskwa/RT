/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:09:35 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 02:09:35 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include "../../includes/texture.h"
#include "../../includes/Sphere.h"

static int get_color(float azi, float ele, t_img *texture)
{
	int	x;
	int	y;
	int	px_s;

	x = ((azi + M_PI) / (2 * M_PI)) * texture->width;
    y = ((ele + M_PI / 2) / M_PI) * texture->height;
	px_s = (y * texture->line_len + x * (texture->bpp / 8));
	return (get_rgb(texture->addr[px_s],
				 texture->addr[px_s + 1],
				 texture->addr[px_s + 2]));
}

static t_v3 update_hit_rot(t_hit hit, t_sp *sp)
{
	t_v3	hit_vec;

	hit_vec = vec_sub(hit.ori, sp->pos);
	hit_vec = (t_v3)
	{
		dot(hit_vec, sp->ri),
		dot(hit_vec, sp->fw),
		dot(hit_vec, sp->up),
		0,
		0
	};
	return (hit_vec);
}

t_co get_sp_texture_color(t_sp *sp, t_hit hit)
{
	t_v3	local_hit;
	float	elevation;
	float	azimuth;
	int	color;
	t_co	col;

	local_hit = norm(update_hit_rot(hit, sp));
	elevation = asin(local_hit.z);
	azimuth = atan2(local_hit.y, local_hit.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	azimuth = adjust_angle(azimuth);
	color = get_color(azimuth, elevation, &sp->tex.b);
	col.r = (float)((color >> 16) & 0xFF) / 255.0f;
	col.g = (float)((color >> 8) & 0xFF) /255.0f;
	col.b = (float)((color) & 0xFF) / 255.0f;
	return (col);
}

t_v3	get_sp_nmap_vec(t_sp *sp, t_hit hit)
{
	t_v3	tmp_vec;
	float	elevation;
	float	azimuth;
	int		x;
	int		y;

	tmp_vec = norm(update_hit_rot(hit, sp));
	elevation = asin(tmp_vec.z);
	azimuth = atan2(tmp_vec.y, tmp_vec.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	azimuth = adjust_angle(azimuth);
	x = ((azimuth + M_PI) / (2 * M_PI)) * sp->tex.n.width;
	y = ((elevation + M_PI / 2) / M_PI) * sp->tex.n.height;
	return (get_nmap_vec(&sp->tex.n, x, y, hit.norm));
}
