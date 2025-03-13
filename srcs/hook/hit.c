/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:52:22 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 09:52:22 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include <stdbool.h>

static bool	hit_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_v3	oc;

	cam_pos = vec_add(cam_pos, ray);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(ray, ray);
	p.b = 2.0f * dot(oc, ray);
	p.c = dot(oc, oc) - sp->dia/2 * sp->dia/2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
		if ((-p.b + sqrt(p.delta)) / (2.0f * p.a)  >= 0
			|| (-p.b - sqrt(p.delta)) / (2.0f * p.a) >= 0)
			return (true);
	return (false);
}

static bool	hit_pl(t_v3 ray, t_pl *pl, t_v3	cam_pos)
{
	float	dist;

	cam_pos = vec_add(cam_pos, ray);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(ray, pl->norm);
	if (dist > 0)
		return (true);
	else
		return (false);
}

#include <stdio.h>
bool	hit_sh(t_v3 ray, t_sc *sc, t_v3 pos, t_sh **sh)
{
	int		i;
	bool	hit;

	i = -1;
	hit = false;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE && hit_sp(ray, sc->elems[i].sh.sp, pos))
		{
			if (sh)
				*sh = &sc->elems[i].sh;
			return (true);
		}
		else if (sc->elems[i].type == PLANE && hit_pl(ray, sc->elems[i].sh.pl, pos))
		{
			if (sh)
				*sh = &sc->elems[i].sh;
			// printf("test\n");
			return (true);
		}
	}
	return (false);
}
