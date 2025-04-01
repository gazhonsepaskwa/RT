/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:23:04 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/01 11:23:04 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/transfo.h"
#include "../../../includes/Minirt.h"
#include "../../../includes/macros.h"
#include "../../../includes/Vec.h"
#include <sys/types.h>

static t_v3	rot_axis(t_v3 v, t_v3 k, float angle)
{
	float	cos_theta;
	float	sin_theta;
	t_v3	t1;
	t_v3	t2;
	t_v3	t3;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	k = norm(k);
	t1 = vec_scale(v, cos_theta);
	t2 = vec_scale(cross(k, v), sin_theta);
	t3 = vec_scale(k, dot(k, v) * (1 - cos_theta));
	return (norm(vec_add(vec_add(t1, t2), t3)));
}

static void	rotation(t_v3	*up, t_v3 *fw, t_v3 *right, float angle)
{
	t_v3	tmp;

	tmp = (t_v3){0, 1, 0, 0, 0};
	*fw = rot_axis(*fw, tmp, angle);
	*right = norm(cross(*fw, tmp));
	*up = norm(cross(*right, *fw));
}

static void	handle_edge_case(t_v3 *up, t_v3 *fw, t_v3 *right, float angle)
{
	t_v3	tmp;

	tmp = (t_v3){0, 1, 0, 0, 0};
	rotate_3axis(XK_Down, up, fw, right);
	rotation(up, fw, right, angle);
	rotate_3axis(XK_Up, up, fw, right);
}

static void	rotate_pitch(t_v3 *up, t_v3 *fw, t_v3 *right, float angle)
{
	*fw = rot_axis(*fw, *right, angle);
	*up = rot_axis(*up, *right, angle);
}

void	rotate_3axis(int keycode, t_v3 *up, t_v3 *fw, t_v3 *right)
{
	t_v3	tmp;

	tmp = (t_v3){0, 1, 0, 0, 0};
	if (keycode == XK_Down)
		rotate_pitch(up, fw, right, -M_PI / 128);
	else if (keycode == XK_Up)
		rotate_pitch(up, fw, right, M_PI / 128);
	else if (keycode == XK_Right)
	{
		if (fabs(dot(*fw, tmp)) > EPSILON)
			handle_edge_case(up, fw, right, -M_PI / 128);
		else
			rotation(up, fw, right, -M_PI / 128);
	}
	else if (keycode == XK_Left)
	{
		if (fabs(dot(*fw, tmp)) > EPSILON)
			handle_edge_case(up, fw, right, M_PI / 128);
		else
			rotation(up, fw, right, M_PI / 128);
	}
}
