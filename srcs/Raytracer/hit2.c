/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:58 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 12:00:58 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
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

bool	hit_shcn(t_v3 ray, t_cn *cn, t_v3 cam_pos, t_li *li)
{
	t_poly	p;
	t_v3	oc;
	float	llen;

	cam_pos = vec_add(cam_pos, vec_scale(ray, 0.01));
	llen = len(vec_sub(li->pos, cam_pos));
	oc = vec_sub(cam_pos, cn->pos);
	p.a = powf(dot(ray, cn->norm), 2) - powf(cos(M_PI / 9), 2);
	p.b = 2.0 * (dot(ray, cn->norm) * dot(oc, cn->norm)
			- powf(cos(M_PI / 9), 2) * dot(ray, oc));
	p.c = powf(dot(oc, cn->norm), 2) - powf(cos(M_PI / 9), 2) * dot(oc, oc);
	p.delta = p.b * p.b - 4.0 * p.a * p.c;
	if (p.delta < 0)
		return (false);
	p.sol = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a),
			(-p.b - sqrt(p.delta)) / (2.0f * p.a));
	if (p.sol <= 0)
		return (false);
	if (p.sol < llen)
		return (true);
	return (false);
}

static	void	swap_val(t_baseop *b)
{
	b->ch1 = b->ch2;
	b->i1 = b->i2;
	b->b1 = b->b2;
}

bool	hit_shbase(t_v3 ray, t_cl *cl, t_v3 cam_pos, float llen)
{
	t_baseop	b;
	t_opcl		op;

	op.oc = vec_scale(cl->norm, cl->h / 2);
	b.b1 = vec_add(cl->pos, op.oc);
	b.b2 = vec_sub(cl->pos, op.oc);
	b.rb1 = vec_sub(b.b1, cam_pos);
	b.rb2 = vec_sub(b.b2, cam_pos);
	b.ch1 = dot(b.rb1, cl->norm) / dot(ray, cl->norm);
	b.ch2 = dot(b.rb2, cl->norm) / dot(ray, cl->norm);
	if (b.ch1 > 0 && b.ch2 > 0)
	{
		b.i1 = vec_add(cam_pos, vec_scale(ray, b.ch1));
		b.i2 = vec_add(cam_pos, vec_scale(ray, b.ch2));
		if (len(vec_sub(b.i1, cam_pos)) > len(vec_sub(b.i2, cam_pos)))
			swap_val(&b);
		b.ip1 = vec_sub(b.i1, b.b1);
		b.len1 = sqrt(b.ip1.x * b.ip1.x + b.ip1.y
				* b.ip1.y + b.ip1.z * b.ip1.z);
		if (b.len1 <= cl->r && b.ch1 < llen)
			return (true);
	}
	return (false);
}
