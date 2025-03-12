/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:24:07 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/12 08:24:07 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Sphere.h"
#include "../../includes/Vec.h"

t_v3	vec_sub(t_v3 a, t_v3 b)
{
	t_v3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

float	len(t_v3 vec)
{
	return (sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
}

t_v3	calc_sp_norm(t_v3 ray, t_sp *sp, t_v3 cam_pos, float dst)
{
	t_v3	res;
	t_v3	Pt;

	Pt = vec_add(cam_pos, vec_scale(ray, dst));
	res = norm(vec_sub(Pt, sp->pos));
	return (res);
}
