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
#include "../../includes/Scene.h"
#include <stdbool.h>

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else
		return (fmin(a, b));
}

static bool	hit_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos, t_li *li)
{
	t_poly	p;
	t_v3	oc;
	float	llen;

	llen = len(vec_sub(li->pos, cam_pos));
	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(ray, ray);
	p.b = 2.0f * dot(oc, ray);
	p.c = dot(oc, oc) - sp->dia / 2 * sp->dia / 2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		p.x1 = -p.b + sqrt(p.delta) / (2.0f * p.a);
		p.x2 = -p.b - sqrt(p.delta) / (2.0f * p.a);
		if ((p.x1 >= 0 || p.x2 >= 0))
		{
			if (len(oc) < llen)
				return (true);
		}
	}
	return (false);
}

static bool	hit_pl(t_v3 ray, t_pl *pl, t_v3	cam_pos, t_li *li)
{
	float	dist;
	float	llen;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	llen = len(vec_sub(li->pos, cam_pos));
	if (dot(ray, pl->norm) == 0.0f)
		return (false);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(ray, pl->norm);
	if (dist > 0 && dist < llen)
		return (true);
	else
		return (false);
}

static bool	hit_cl(t_v3 ray, t_cl *cl, t_v3 cam_pos, t_li *li)
{
	float	llen;
	t_poly	p;
	t_opcl	op;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	llen = len(vec_sub(li->pos, cam_pos));
	op.oc = vec_sub(cam_pos, cl->pos);
	op.r_p = vec_sub(ray, vec_scale(cl->norm, dot(cl->norm, ray)));
	op.oc_p = vec_sub(op.oc, vec_scale(cl->norm, dot(cl->norm, op.oc)));
	p.a = dot(op.r_p, op.r_p);
	p.b = 2.0f * dot(op.oc_p, op.r_p);
	p.c = dot(op.oc_p, op.oc_p) - cl->r * cl->r;
	p.delta = p.b * p.b - 4.0f * p.a * p.c;
	if (p.delta < 0)
		return (false);
	p.x1 = (-p.b + sqrt(p.delta)) / (2.0 * p.a);
	p.x2 = (-p.b - sqrt(p.delta)) / (2.0 * p.a);
	p.sol = fminpos(p.x1, p.x2);
	if (p.sol <= 0)
		return (false);
	op.pt = vec_add(cam_pos, vec_scale(ray, p.sol));
	p.x1 = dot(vec_sub(op.pt, cl->pos), cl->norm);
	if (fabs(p.x1) <= cl->h / 2 && p.sol < llen)
		return (true);
	return (hit_shbase(ray, cl, cam_pos, llen));
}

bool	hit_sh(t_v3 ray, t_sc *sc, t_v3 pos)
{
	int		i;
	bool	hit;
	t_li	*li;

	i = -1;
	hit = false;
	li = getlight(sc);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE
			&& hit_sp(ray, sc->elems[i].sh.sp, pos, li))
			return (true);
		else if (sc->elems[i].type == PLANE
			&& hit_pl(ray, sc->elems[i].sh.pl, pos, li))
			return (true);
		else if (sc->elems[i].type == CYLINDER
			&& hit_cl(ray, sc->elems[i].sh.cl, pos, li))
			return (true);
		else if (sc->elems[i].type == CONE
			&& hit_shcn(ray, sc->elems[i].sh.cn, pos, li))
			return (true);
	}
	return (false);
}
