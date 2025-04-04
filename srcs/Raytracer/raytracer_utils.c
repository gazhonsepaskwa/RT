/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:57:46 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/12 08:57:46 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include <stdlib.h>

t_hit	init_hit(t_v3 ray, t_v3 cam_pos)
{
	t_hit	hit;

	hit.hit = false;
	hit.ray = ray;
	hit.ori = cam_pos;
	hit.col = (t_co){1, 1, 1};
	return (hit);
}

int	calc_color(t_co col, float factor, t_sc *sc)
{
	float	r;
	float	g;
	float	b;

	r = col.r * factor * sc->li * sc->col.r;
	g = col.g * factor * sc->li * sc->col.g;
	b = col.b * factor * sc->li * sc->col.b;
	r = clump(r, 0.0f, 1.0f) * 255;
	g = clump(g, 0.0f, 1.0f) * 255;
	b = clump(b, 0.0f, 1.0f) * 255;
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

bool	haslight(t_hit *hit, t_sc *sc)
{
	t_li	*li;
	t_v3	to_li;
	int		i;
	bool	check;

	i = -1;
	check = false;
	while (++i < sc->nb_lig)
	{
		li = sc->lig[i];
		to_li = vec_sub(li->pos, vec_add(hit->ori,
					vec_scale(hit->norm, 0.01f)));
		to_li = norm(to_li);
		if (dot(to_li, hit->norm) >= 0)
		{
			check = hit_sh(to_li, sc, hit->ori, li);
			if (!check)
				return (true);
		}
	}
	return (false);
}

void	eval_hit_color(t_hit *hit, t_sc *sc)
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

void	init_lut(float lut[2][256], int *init)
{
	int		i;
	float	coeff;

	i = -1;
	coeff = 1 / 1.5;
	while (++i < 256)
		lut[0][i] = powf(i / 255.0f, coeff);
	i = -1;
	while (++i < 256)
		lut[1][i] = clump(powf(i / 255.0f, 1.2),
				0.0f, 1.0f);
	*init = 1;
}
