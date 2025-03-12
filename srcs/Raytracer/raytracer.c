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
#include <stdio.h>

static int calc_color(int color, float factor)
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

static t_hit	draw_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_hit	hit;
	t_v3	oc;

	hit = init_hit(ray);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(ray, ray);
	p.b = 2.0f * dot(oc, ray);
	p.c = dot(oc, oc) - sp->dia/2 * sp->dia/2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		hit.dst = fmin((-p.b + sqrt(p.delta)) / (2.0f * p.a), (-p.b - sqrt(p.delta)) / (2.0f * p.a));
		if (hit.dst >= 0)
		{
			hit.hit = true;
			hit.norm = calc_sp_norm(ray, sp, cam_pos, hit.dst);
			hit.color = sp->col;
			// hit.color = calc_color(sp->col, 1 - (hit.dst / len(oc)));
		}
	}
	return (hit);
}

static void	draw_sh(t_v3 ray, t_sc *sc, t_img *img, t_v3 pos)
{
	int	i;
	t_hit	hit;

	i = -1;
	hit = init_hit(ray);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			hit = draw_sp(ray, sc->elems[i].sh.sp, pos);
		if (hit.hit)
			mlx_put_px(img, ray.px, ray.py, calc_color(hit.color, sc->li));
		// else 
			// mlx_put_px(img, ray.px, ray.py, calc_color((8 << 16) | (195 << 8) | 252, 0.3));
	}
}

void	raytrace(t_sc *sc, t_img *img)
{
	t_ca	cam;
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
			draw_sh(ray, sc, img, cam.pos);
			// fprintf(file, "|j:%3d| |i:%3d| |ray.x=%f| |ray.y=%f| |ray.z=%f|\n", j, i, ray.x, ray.y, ray.z);
		}
	}
	// fclose(file);
}
