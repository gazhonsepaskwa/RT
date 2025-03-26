/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:56 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 12:13:56 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Sphere.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/texture.h"

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else
		return (fmin(a, b));
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

t_hit	draw_sp(t_hit tmp, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_hit	hit;
	t_v3	oc;

	hit = init_hit(tmp.ray, cam_pos);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(tmp.ray, tmp.ray);
	p.b = 2.0f * dot(oc, tmp.ray);
	p.c = dot(oc, oc) - (sp->dia / 2 * sp->dia / 2);
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		hit.dst = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a),
				(-p.b - sqrt(p.delta)) / (2.0f * p.a));
		if (hit.dst >= 0 && (!tmp.hit || (tmp.dst > 0 && hit.dst < tmp.dst)))
			update_hit(tmp.ray, &hit, cam_pos, sp);
	}
	return (hit);
}
