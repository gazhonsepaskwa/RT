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
