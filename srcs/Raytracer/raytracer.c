/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:32:10 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/03 14:22:06 by lderidde         ###   ########.fr       */
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
#include "../../includes/Menu.h"
#include "../../includes/hook.h"
#include <unistd.h>

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

static int	get_hdri_texture_color(t_sp *sp, t_hit hit)
{
	float			angles[2];
	static float	lut[2][256];
	static int		init = 0;
	int				color;
	t_co			col;

	if (access("./assets/HDRI/hdri.xpm", F_OK | R_OK) != 0)
		return (0x0087CEEB);
	if (init == 0)
		init_lut(lut, &init);
	angles[0] = asin(-hit.ray.y);
	angles[1] = atan2(hit.ray.z, hit.ray.x);
	adjust_elevation_azimuth(&angles[0], &angles[1]);
	angles[1] = adjust_angle(angles[1]);
	color = get_color(angles[1], angles[0], &sp->tex.b);
	col = (t_co){((color >> 16) & 0xFF), ((color >> 8) & 0xFF),
		((color) & 0xFF)};
	if ((int)col.r > 40 && (int)col.g > 40 && (int)col.b > 40)
		col = (t_co){lut[1][(int)col.r], lut[1][(int)col.g],
			lut[1][(int)col.b]};
	else
		col = (t_co){lut[0][(int)col.r], lut[0][(int)col.g],
			lut[0][(int)col.b]};
	return (((int)(col.r * 255) << 16) | ((int)(col.g * 255) << 8)
		| ((int)(col.b * 255)));
}

void	render_line(t_img *img, int rbs, t_mrt *mrt, int line)
{
	t_xy	i;
	t_hit	hit;
	t_xy	rec_lim;
	int		col;

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
			mlx_put_rect(img, i, rec_lim, col);
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
	mrt->draw_menu = false;
}
