/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                            +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:32:10 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:32:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Objects/Cylinder.h"
#include "../../includes/Objects/Sphere.h"
#include "../../includes/Objects/Plane.h"
#include "../../includes/Objects/Light.h"
#include "../../includes/Objects/Cam.h"
#include "../../includes/Raytracer.h"
#include "../../includes/texture.h"
#include "../../includes/Minirt.h"
#include "../../includes/macros.h"
#include "../../includes/Scene.h"
#include "../../includes/hook.h"

static t_hit	draw_sh(t_v3 ray, t_sc *sc, t_img *img, t_v3 pos)
{
	int		i;
	t_hit	hit;
	t_hit	tmp;

	i = -1;
	(void)img;
	hit = init_hit(ray, pos);
	tmp = init_hit(ray, pos);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			tmp = draw_sp(hit, sc->elems[i].sh.sp, pos);
		else if (sc->elems[i].type == PLANE)
			tmp = draw_pl(hit, sc->elems[i].sh.pl, pos);
		else if (sc->elems[i].type == CYLINDER)
			tmp = draw_cl(hit, sc->elems[i].sh.cl, pos);
		else if (sc->elems[i].type == CONE)
			tmp = draw_cn(hit, sc->elems[i].sh.cn, pos);
		if (tmp.hit && (!hit.hit || (tmp.dst > 0 && tmp.dst < hit.dst)))
			hit = tmp;
	}
	eval_hit_color(&hit, sc);
	return (hit);
}

static t_hit	raytrace_px(t_sc *sc, t_img *img, t_xy *px)
{
	float	co[2];
	t_ca	cam;
	t_v3	ray;
	t_hit	hit;

	cam = *(sc->cam);
	co[0] = (2 * ((px->x + 0.5) / WIDTH) - 1) * cam.asp * cam.scale;
	co[1] = (1 - 2 * ((px->y + 0.5) / HEIGHT)) * cam.scale;
	ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
					vec_scale(cam.up, co[1])), cam.fw));
	hit = draw_sh(ray, sc, img, cam.pos);
	return (hit);
}

static t_co	get_hdri_texture_color(t_sp *sp, t_hit hit)
{
	t_v3	local_hit;
	float	elevation;
	float	azimuth;
	int		color;
	t_co	col;

	local_hit = hit.ray;
	elevation = asin(-local_hit.y);
	azimuth = atan2(local_hit.z, local_hit.x);
	adjust_elevation_azimuth(&elevation, &azimuth);
	azimuth = adjust_angle(azimuth);
	color = get_color(azimuth, elevation, &sp->tex.b);
	col.b = (float)((color >> 16) & 0xFF) / 255.0f;
	col.g = (float)((color >> 8) & 0xFF) / 255.0f;
	col.r = (float)((color) & 0xFF) / 255.0f;
	return (col);
}

void	render_line(t_img *img, int rbs, t_mrt *mrt, int line)
{
	t_xy	i;
	t_hit	hit;
	t_xy	rec_lim;
	t_co	col;

	i.x = 0;
	i.y = line;
	while (i.x < WIDTH)
	{
		hit = raytrace_px(mrt->sc, img, &i);
		rec_lim = (t_xy){i.x + rbs, line + rbs};
		if (hit.hit)
			mlx_put_rect(img, i, rec_lim, hit.color);
		else
		{
			col = get_hdri_texture_color(&mrt->sc->hdri, hit);
			mlx_put_rect(img, i, rec_lim, get_rgb((int)(col.r * 255),
					(int)(col.g * 255), (int)(col.b * 255)));
		}
		i.x += rbs;
	}
}

void	render_frame(t_img *img, int rbs, t_mrt *mrt)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		render_line(img, rbs, mrt, y);
		y += rbs;
	}
}
