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

static void	draw_sp(t_v3 ray, t_sp *sp, t_img *img, t_v3 rayo)
{
	float	a;
	float	b;
	float	c;
	t_v3	oc;
	float	delta;

	oc.x = rayo.x - sp->pos.x;
	oc.y = rayo.y - sp->pos.y;
	oc.z = rayo.z - sp->pos.z;
	a = dot(ray, ray);
	b = 2.0f * dot(oc, ray);
	c = dot(oc, oc) - sp->dia/2 * sp->dia/2;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		if ((-b + sqrt(delta)) / (2.0f * a) >= 0 || (-b - sqrt(delta)) / (2.0f * a) >= 0)
			mlx_put_px(img, ray.px, ray.py, sp->col);
	}
}

static void	draw_sh(t_v3 ray, t_sc *sc, t_img *img, t_v3 pos)
{
	int	i;

	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			draw_sp(ray, sc->elems[i].sh.sp, img, pos);
	}
	
}

void	raytrace(t_sc *sc, t_img *img)
{
	t_ca	cam;
	int		j;
	float	co[2];
	t_v3	ray;
	int		i;
	FILE *file;

	cam = get_cam(sc);
	file = fopen("rays.log", "w");
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
	fclose(file);
}
