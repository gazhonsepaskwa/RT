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

static float adjust_angle(float angle)
{
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	return angle;
}

static void adjust_elevation_azimuth(float *elevation, float *azimuth)
{
	if (*elevation > M_PI / 2)
	{
		*elevation = M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
	else if (*elevation < -M_PI / 2)
	{
		*elevation = -M_PI - *elevation;
		*azimuth = adjust_angle(*azimuth + M_PI);
	}
}

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

int get_sp_texture_color(t_sp *sp, t_hit hit)
{
	t_v3	local_hit;
	float	elevation;
	float	azimuth;

	local_hit = norm(update_hit_rot(hit, sp));
	elevation = asin(local_hit.z);
	azimuth = atan2(local_hit.y, local_hit.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	azimuth = adjust_angle(azimuth);
	return (get_color(azimuth, elevation, &sp->tex.b));
}

t_v3	get_sp_nmap_vec(t_sp *sp, t_hit hit)
{
	t_v3	tmp_vec;
	float	elevation;
	float	azimuth;
	int		x;
	int		y;

	sp->ri = norm(cross((t_v3){0, 0, 1, 0, 0}, sp->up));
	if (len(sp->ri) < 0.001f)
		sp->ri = (t_v3){1, 0, 0, 0, 0};
	sp->fw = cross(sp->up, sp->ri);
	tmp_vec = norm(update_hit_rot(hit, sp));
	elevation = asin(tmp_vec.z);
	azimuth = atan2(tmp_vec.y, tmp_vec.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	azimuth = adjust_angle(azimuth);
	x = ((azimuth + M_PI) / (2 * M_PI)) * sp->tex.n.width;
	y = ((elevation + M_PI / 2) / M_PI) * sp->tex.n.height;
	tmp_vec = get_nmap_vec(&sp->tex.n, x, y);
	elevation = asin(tmp_vec.z);
	azimuth = atan2(tmp_vec.y, tmp_vec.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	rot_x(tmp_vec, azimuth);
	rot_y(tmp_vec, elevation);
	return (tmp_vec);
}
