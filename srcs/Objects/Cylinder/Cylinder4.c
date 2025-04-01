/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:16:32 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 11:16:32 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cylinder.h"
#include "../../../includes/Raytracer.h"

void	calc_hit_both(t_baseop b, t_v3 cam, t_cl *cl, t_hit *hit)
{
	b.i1 = vec_add(cam, vec_scale(hit->ray, b.ch1));
	b.i2 = vec_add(cam, vec_scale(hit->ray, b.ch2));
	if (len(vec_sub(b.i1, cam)) > len(vec_sub(b.i2, cam)))
	{
		b.ch1 = b.ch2;
		b.i1 = b.i2;
		b.b1 = b.b2;
	}
	b.ip1 = vec_sub(b.i1, b.b1);
	b.len1 = sqrt(b.ip1.x * b.ip1.x + b.ip1.y
			* b.ip1.y + b.ip1.z * b.ip1.z);
	if (b.len1 <= cl->r)
		return (update_bcl2hit(hit, cl, b));
}

void	calc_hit_top(t_baseop b, t_hit *hit, t_cl *cl)
{
	b.i1 = vec_add(hit->ori, vec_scale(hit->ray, b.ch1));
	b.ip1 = vec_sub(b.i1, b.b1);
	b.len1 = sqrt(b.ip1.x * b.ip1.x + b.ip1.y
			* b.ip1.y + b.ip1.z * b.ip1.z);
	if (b.len1 <= cl->r)
		return (update_bcluphit(hit, cl, b));
}
