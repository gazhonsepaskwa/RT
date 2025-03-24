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

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int calc_color(t_co col, float factor)
{
    int r;
    int g;
    int b;

    r =	col.r * 255; 
    g = col.g * 255;
    b = col.b * 255;
	r = r * factor;
	if (r > 255)
		r = 255;
	g = g * factor;
	if (g > 255)
		g = 255;
	b = b * factor;
	if (b > 255)
		b = 255;
    return ((r << 16) | (g << 8) | b);
}

static void	update_hit(t_v3 ray, t_hit *hit, t_v3 cam_pos, t_sp *sp)
{
	hit->hit = true;
	hit->ori = vec_add(cam_pos, vec_scale(ray, hit->dst));
	hit->norm = calc_sp_norm(ray, sp, cam_pos, hit->dst);
	hit->norm = get_sp_nmap_vec(sp, *hit);
	hit->ref = vec_sub(ray, vec_scale(hit->norm, 2 * dot(ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->r_ray = vec_scale(ray, -1);
}

bool	hasLight(t_hit *hit, t_sc *sc)
{
	t_li	*li;
	t_v3	toLi;

	li = getLight(sc);
	if (!li)
		return (false);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	if (dot(toLi, hit->norm) > 0)
		return (!hit_sh(toLi, sc, hit->ori, NULL)); // vec_scale(hit->ori, 1.0000f)
	// printf("test2\n");
	return (false);
}

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else return fmin(a, b);
}

static t_hit	draw_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos, t_sc *sc)
{
	t_poly	p;
	t_hit	hit;
	t_v3	oc;

	hit = init_hit(ray, cam_pos);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(ray, ray);
	p.b = 2.0f * dot(oc, ray);
	p.c = dot(oc, oc) - (sp->dia-(sp->dia/100))/2 * (sp->dia-(sp->dia/100))/2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		hit.dst = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a), (-p.b - sqrt(p.delta)) / (2.0f * p.a));
		if (hit.dst >= 0)
		{
			update_hit(ray, &hit, cam_pos, sp);
			sp->col = get_sp_texture_color(sp, hit);
			if (hasLight(&hit, sc))
				hit.color = add_light_sp(sp, sc, &hit);
			else
				hit.color = calc_color(sp->col, sp->ma.ka * sc->li);
		}
	}
	return (hit);
}

static t_hit	draw_pl(t_v3 ray, t_pl *pl, t_v3 cam_pos, t_sc *sc)
{
	t_hit	hit;
	float	dist;

	hit = init_hit(ray, cam_pos);
	if (dot(ray, pl->norm) == 0.0f)
		return (hit);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(ray, pl->norm);
	if (dist > 0)
	{
		hit.dst = dist;
		hit.hit = true;
		hit.ori = vec_add(cam_pos, vec_scale(ray, hit.dst));
		hit.norm = pl->norm;
		hit.norm = get_pl_nmap_vec(pl, hit);
		hit.ref = vec_sub(ray, vec_scale(hit.norm, 2 * dot(ray, hit.norm)));
		hit.ref = norm(hit.ref);
		// pl->col = get_pl_texture_color(pl, hit);
		if (hasLight(&hit, sc))
			hit.color = add_light_pl(pl, sc, &hit);
		else
			hit.color = calc_color(pl->col, pl->ma.ka * sc->li);
	}
	return (hit);
}

static t_hit	draw_sh(t_v3 ray, t_sc *sc, t_img *img, t_v3 pos)
{
	int	i;
	t_hit	hit;
	t_hit	tmp;

	i = -1;
	(void)img;
	hit = init_hit(ray, pos);
	tmp = init_hit(ray, pos);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			tmp = draw_sp(ray, sc->elems[i].sh.sp, pos, sc);
		else if (sc->elems[i].type == PLANE)
			tmp = draw_pl(ray, sc->elems[i].sh.pl, pos, sc);
		else if (sc->elems[i].type == CYLINDER)
			tmp = draw_cl(ray, sc->elems[i].sh.cl, pos, sc);
		if (tmp.hit && (!hit.hit || (tmp.dst > 0 && tmp.dst < hit.dst)))
			hit = tmp;
	}
	return (hit);
}

static t_hit	raytrace_px(t_sc *sc, t_img *img, t_xy px)
{
	float	co[2];
	t_ca	cam;
	t_v3	ray;
	t_hit	hit;

	cam = *(sc->cam);
	co[0] = (2 * ((px.x + 0.5)/WIDTH) - 1) * cam.asp * cam.scale;
	co[1] = (1 - 2 * ((px.y+ 0.5) / HEIGHT)) * cam.scale;
	ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
			vec_scale(cam.up, co[1])), cam.fw));
	hit = draw_sh(ray, sc, img, cam.pos);
	return (hit);
}

void	render_line(t_img *img, int rbs, t_mrt *mrt, int line)
{
	t_xy	i;
	t_hit	hit;
	t_xy	rec_lim;

	i.x = 0;
	i.y = line;
	while (i.x < WIDTH)
	{
		hit = raytrace_px(mrt->sc, img, i);
		rec_lim = (t_xy){i.x + rbs, line + rbs};
		if (hit.hit)
			mlx_put_rect(img, i, rec_lim, hit.color);
		else
			mlx_put_rect(img, i, rec_lim, 0x0087CEEB);
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
