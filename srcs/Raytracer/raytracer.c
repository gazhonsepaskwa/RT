/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:32:10 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:32:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include "../../includes/Plane.h"
#include "../../includes/hook.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int calc_color(int color, float factor)
{
    int r;
    int g;
    int b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
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
	hit->norm = calc_sp_norm(ray, sp, cam_pos, hit->dst);
	hit->ori = vec_add(cam_pos, vec_scale(ray, hit->dst));
}

static bool	hasLight(t_hit *hit, t_sc *sc)
{
	t_li	*li;
	t_v3	toLi;

	li = getLight(sc);
	if (!li)
		return (false);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	if (dot(toLi, hit->norm) > 0)
		return (hit_sh(toLi, sc, hit->ori, NULL)); // vec_scale(hit->ori, 1.0000f)
	return (false);
}

static int add_light_sp(t_sp *sp, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	double	theta;

	li = getLight(sc);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	theta = acos(dot(toLi, hit->norm));
	return (calc_color(sp->col, li->li * cos(theta)));
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

	hit = init_hit(ray);
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
			if (hasLight(&hit, sc))
				hit.color = (int)fmax(add_light_sp(sp, sc, &hit), calc_color(sp->col, sc->li));
			else
				hit.color = calc_color(sp->col, sc->li);
		}
	}
	return (hit);
}

static t_hit	draw_pl(t_v3 ray, t_pl *pl, t_v3 cam_pos, t_sc *sc)
{
	t_hit	hit;
	float	dist;

	hit = init_hit(ray);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(ray, pl->norm);
	if (dist > 0)
	{
		hit.dst = dist;
		hit.hit = true;
		hit.norm = pl->norm;
		hit.ori = vec_add(cam_pos, vec_scale(ray, hit.dst));
		if (hasLight(&hit, sc))
			hit.color = (int)fmax(add_light_pl(pl, sc, &hit), calc_color(pl->col, sc->li));
		else
			hit.color = calc_color(pl->col, sc->li);
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
	hit = init_hit(ray);
	tmp = init_hit(ray);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			tmp = draw_sp(ray, sc->elems[i].sh.sp, pos, sc);
		if (sc->elems[i].type == PLANE)
			tmp = draw_pl(ray, sc->elems[i].sh.pl, pos, sc);
		if (tmp.hit && (!hit.hit || (tmp.dst > 0 && tmp.dst < hit.dst)))
			hit = tmp;
	}
	return (hit);
}

void	raytrace(t_sc *sc, t_img *img)
{
	t_ca	cam;
	t_hit	hit;
	int		j;
	float	co[2];
	t_v3	ray;
	int		i;
	// FILE *file;

	cam = *(sc->cam);
	// file = fopen("rays.log", "w");
	printf("cam.pos.x=%f\ncam.pos.y=%f\ncam.pos.z=%f\ncam.fw.x=%f\ncam.fw.y=%f\ncam.fw.z=%f\ncam.fov=%f\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.fw.x, cam.fw.y, cam.fw.z, cam.fov);
	printf("cam.up.x=%f\ncam.up.y=%f\ncam.up.z=%f\ncam.right.x=%f\ncam.right.y=%f\ncam.right.z=%f\ncam.scale=%f\ncam.asp=%f\n", cam.up.x, cam.up.y, cam.up.z, cam.right.x, cam.right.y, cam.right.z, cam.scale, cam.asp);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			co[0] = (2 * ((i + 0.5)/WIDTH) - 1) * cam.asp * cam.scale;
			co[1] = (1 - 2 * ((j+ 0.5) / HEIGHT)) * cam.scale;
			ray = norm(vec_add(vec_add(vec_scale(cam.right, co[0]),
					vec_scale(cam.up, co[1])), cam.fw));
			ray.py = j;
			ray.px = i;
			hit = draw_sh(ray, sc, img, cam.pos);
			if (hit.hit)
				mlx_put_px(img, ray.px, ray.py, hit.color);
			// fprintf(file, "|j:%3d| |i:%3d| |ray.x=%f| |ray.y=%f| |ray.z=%f|\n", j, i, ray.x, ray.y, ray.z);
			// i += 2;
		}
	}
	// fclose(file);
}
