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

#include <stdio.h>
#include <math.h>

int calc_color(t_co col, float factor, t_sc *sc)
{
    float r;
    float g;
    float b;

    r =	col.r * factor * sc->li * sc->col.r; 
    g = col.g * factor * sc->li * sc->col.g;
    b = col.b * factor * sc->li * sc->col.b;
	r = clump(r, 0.0f, 1.0f) * 255;
	g = clump(g, 0.0f, 1.0f) * 255;
	b = clump(b, 0.0f, 1.0f) * 255;
    return (((int)r << 16) | ((int)g << 8) | (int)b);
}

static void	update_hit(t_v3 ray, t_hit *hit, t_v3 cam_pos, t_sp *sp)
{
	hit->hit = true;
	hit->ori = vec_add(cam_pos, vec_scale(ray, hit->dst));
	hit->norm = calc_sp_norm(ray, sp, cam_pos, hit->dst);
	if (sp->tex.existn)
		hit->norm = get_sp_nmap_vec(sp, *hit);
	hit->ref = vec_sub(ray, vec_scale(hit->norm, 2 * dot(ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->r_ray = vec_scale(ray, -1);
	hit->sh = sp;
	hit->type = SPHERE;
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
	if (dot(toLi, hit->norm) >= 0)
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

static t_hit	draw_sp(t_hit tmp, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_hit	hit;
	t_v3	oc;

	hit = init_hit(tmp.ray, cam_pos);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(tmp.ray, tmp.ray);
	p.b = 2.0f * dot(oc, tmp.ray);
	p.c = dot(oc, oc) - (sp->dia-(sp->dia/100))/2 * (sp->dia-(sp->dia/100))/2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		hit.dst = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a), (-p.b - sqrt(p.delta)) / (2.0f * p.a));
		if (hit.dst >= 0 && (!tmp.hit || (tmp.dst > 0 && hit.dst < tmp.dst)))
			update_hit(tmp.ray, &hit, cam_pos, sp);
	}
	return (hit);
}

static t_hit	draw_pl(t_hit tmp, t_pl *pl, t_v3 cam_pos)
{
	t_hit	hit;
	float	dist;

	hit = init_hit(tmp.ray, cam_pos);
	if (dot(tmp.ray, pl->norm) == 0.0f)
		return (hit);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(tmp.ray, pl->norm);
	if (dist > 0 && (!tmp.hit || (tmp.dst > 0 && dist < tmp.dst)))
	{
		hit.dst = dist;
		hit.hit = true;
		hit.ori = vec_add(cam_pos, vec_scale(tmp.ray, hit.dst));
		if (dot(tmp.ray, pl->norm) < 0)
			hit.norm = pl->norm;
		else
			hit.norm = vec_scale(pl->norm, -1.0);
		if (pl->tex.existn)
			hit.norm = get_pl_nmap_vec(pl, hit);
		hit.ref = vec_sub(tmp.ray, vec_scale(hit.norm, 2 * dot(tmp.ray, hit.norm)));
		hit.ref = norm(hit.ref);
		hit.sh = pl;
		hit.type = PLANE;
	}
	return (hit);
}

static void	eval_hit_color(t_hit *hit, t_sc *sc)
{
	if (!hit->hit)
		return ;
	if (hit->type == SPHERE)
		eval_color_sp(hit, sc, (t_sp *)hit->sh);
	else if (hit->type == PLANE)
		eval_color_plane(hit, sc, (t_pl *)hit->sh);
	else if (hit->type == CONE)
		eval_color_cone(hit, sc, (t_cn *)hit->sh);
	else if (hit->type == CYLINDER)
		eval_color_cl(hit, sc, (t_cl *)hit->sh);
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
