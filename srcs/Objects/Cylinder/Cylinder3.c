/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:04:24 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 11:04:24 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cylinder.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/Scene.h"

void	update_hitcl(t_hit *hit, t_poly p, t_cl *cl)
{
	t_v3	oc;
	t_v3	proj;

	hit->hit = true;
	hit->dst = p.sol;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	oc = vec_sub(hit->ori, cl->pos);
	proj = vec_scale(cl->norm, dot(oc, cl->norm));
	hit->norm = norm(vec_sub(oc, proj));
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm,
				2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->sh = cl;
	hit->type = CYLINDER;
}

void	update_bcl2hit(t_hit *hit, t_cl *cl, t_baseop b)
{
	t_v3	tob1;
	t_v3	tob2;

	hit->hit = true;
	hit->dst = b.ch1;
	hit->ori = b.i1;
	tob1 = vec_sub(b.b1, hit->ori);
	tob2 = vec_sub(b.b2, hit->ori);
	if (len(tob1) < len(tob2))
		hit->norm = cl->norm;
	else
		hit->norm = vec_scale(cl->norm, -1);
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm,
				2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->sh = cl;
	hit->type = CYLINDER;
}

void	update_bcluphit(t_hit *hit, t_cl *cl, t_baseop b)
{
	hit->hit = true;
	hit->dst = b.ch1;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	hit->norm = cl->norm;
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm,
				2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->sh = cl;
	hit->type = CYLINDER;
}

void	update_bcldhit(t_hit *hit, t_cl *cl, t_baseop b)
{
	hit->hit = true;
	hit->dst = b.ch2;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	hit->norm = vec_scale(cl->norm, -1);
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm,
				2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->sh = cl;
	hit->type = CYLINDER;
}
