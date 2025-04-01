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

#include "../../includes/Objects/Sphere.h"
#include "../../includes/macros.h"
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
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_v3	calc_sp_norm(t_v3 ray, t_sp *sp, t_v3 cam_pos, float dst)
{
	t_v3	res;
	t_v3	pt;

	pt = vec_add(cam_pos, vec_scale(ray, dst));
	res = norm(vec_sub(pt, sp->pos));
	return (res);
}

void	initaxis(t_v3 _norm, t_v3 *x, t_v3 *y)
{
	t_v3	tmp;

	if (fabs(dot(_norm, (t_v3){0, 0, 1, 0, 0})) > EPSILON)
		tmp = (t_v3){1, 0, 0, 0, 0};
	else
		tmp = (t_v3){0, 0, 1, 0, 0};
	*x = norm(cross(_norm, tmp));
	*y = norm(cross(_norm, *x));
}

t_v3	reflectdir(t_v3 v, t_v3 n)
{
	float	val;
	t_v3	ret;

	val = dot(n, v);
	ret.x = v.x - 2 * val * n.x;
	ret.y = v.y - 2 * val * n.y;
	ret.z = v.z - 2 * val * n.z;
	return (ret);
}
