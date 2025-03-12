/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:12:30 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:12:30 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Vec.h"

t_v3	cross(t_v3 a, t_v3 b)
{
	t_v3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_v3	norm(t_v3 vec)
{
	t_v3	res;
	double	len;

	len = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	res.x = vec.x / len;
	res.y = vec.y / len;
	res.z = vec.z / len;
	return (res);
}

t_v3	vec_add(t_v3 v1, t_v3 v2)
{
	t_v3	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_v3	vec_scale(t_v3 vec, float scale)
{
	t_v3	res;

	res.x = vec.x * scale;
	res.y = vec.y * scale;
	res.z = vec.z * scale;
	return (res);
}

float	dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
