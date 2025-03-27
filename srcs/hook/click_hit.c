/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:58:30 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/25 11:58:30 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include "../../includes/Minirt.h"
#include "../../includes/Scene.h"

#include <stdbool.h>

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else return fmin(a, b);
}

static float	hit_sp(t_v3 ray, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_v3	oc;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(ray, ray);
	p.b = 2.0f * dot(oc, ray);
	p.c = dot(oc, oc) - sp->dia/2 * sp->dia/2;
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		p.x1 = -p.b + sqrt(p.delta) / (2.0f * p.a);
		p.x2 = -p.b - sqrt(p.delta) / (2.0f * p.a);
		if ((p.x1 >= 0 || p.x2 >= 0))
				return (fminpos(p.x1, p.x2));
	}
	return (-1);
}

static float	hit_pl(t_v3 ray, t_pl *pl, t_v3	cam_pos)
{
	float	dist;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	if (dot(ray, pl->norm) == 0.0f)
		return (-1);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(ray, pl->norm);
	if (dist > 0)
		return (dist);
	else
		return (-1);
}

static float	hit_cl(t_v3 ray, t_cl *cl, t_v3 cam_pos)
{
	t_poly	p;
	t_opcl	op;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	op.oc = vec_sub(cam_pos, cl->pos);
	op.r_p = vec_sub(ray, vec_scale(cl->norm, dot(cl->norm, ray)));
	op.oc_p = vec_sub(op.oc, vec_scale(cl->norm, dot(cl->norm, op.oc)));
	p.a = dot(op.r_p, op.r_p);
	p.b = 2.0f * dot(op.oc_p, op.r_p);
	p.c = dot(op.oc_p, op.oc_p) - cl->r*cl->r;
	p.delta = p.b*p.b - 4.0f * p.a * p.c;
	if (p.delta < 0)
		return (-1);
	p.x1 = (-p.b + sqrt(p.delta)) / (2.0 * p.a);
	p.x2 = (-p.b - sqrt(p.delta)) / (2.0 * p.a);
	p.sol = fminpos(p.x1, p.x2);
	if (p.sol <= 0)
		return (-1);
	op.pt = vec_add(cam_pos, vec_scale(ray, p.sol));
	p.x1 = dot(vec_sub(op.pt, cl->pos), cl->norm);
	if (fabs(p.x1) <= cl->h / 2)
		return (p.sol);
	return (-1);
}

static float	hit_cn(t_v3 ray, t_cn *cn, t_v3 cam_pos)
{
	t_poly	p;
	t_v3	oc;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	oc = vec_sub(cam_pos, cn->pos);
	p.a = powf(dot(ray, cn->norm), 2) - powf(cos(M_PI / 9), 2);
	p.b = 2.0 * (dot(ray, cn->norm) *
		dot(oc, cn->norm) - powf(cos(M_PI / 9), 2) * dot(ray, oc));
	p.c = powf(dot(oc, cn->norm), 2) - powf(cos(M_PI / 9), 2) * dot(oc, oc);
	p.delta = p.b*p.b - 4.0 * p.a * p.c;
	if (p.delta < 0)
		return (-1);
	p.sol = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a),
				 (-p.b - sqrt(p.delta)) / (2.0f * p.a));
	if (p.sol <= 0)
		return (-1);
	return (p.sol);
}

int nmin(int tmp, int *min_dst)
{
	if (tmp < *min_dst && tmp != -1)
	{
		*min_dst = tmp;
		return (1);
	}
	return (0);
}


t_curent_obj	mouse_hit_sh(t_v3 ray, t_sc *sc, t_v3 pos)
{
	int				min_dst;
	t_curent_obj	out;
	int				i;

	min_dst = 2147483647;
	out = (t_curent_obj){NOTHING, (void *)0};
	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			if (nmin(hit_sp(ray, sc->elems[i].sh.sp, pos), &min_dst))
				out = (t_curent_obj){OBJ_SP, sc->elems[i].sh.sp};
		if (sc->elems[i].type == PLANE)
			if (nmin(hit_pl(ray, sc->elems[i].sh.pl, pos), &min_dst))
				out = (t_curent_obj){OBJ_PL, sc->elems[i].sh.pl};
		if (sc->elems[i].type == CYLINDER)
			if (nmin(hit_cl(ray, sc->elems[i].sh.cl, pos), &min_dst))
				out = (t_curent_obj){OBJ_CL, sc->elems[i].sh.cl};
		if (sc->elems[i].type == CONE)
			if (nmin(hit_cn(ray, sc->elems[i].sh.cn, pos), &min_dst))
				out = (t_curent_obj){OBJ_CN, sc->elems[i].sh.cn};
	}
	return (out);
}
