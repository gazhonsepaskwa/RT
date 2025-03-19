/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:07:53 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:07:53 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <math.h>

typedef struct s_sp	t_sp;

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
	int		px;
	int		py;
}	t_v3;

typedef struct s_mat3x3
{
	float	c1r1;
	float	c1r2;
	float	c1r3;
	float	c2r1;
	float	c2r2;
	float	c2r3;
	float	c3r1;
	float	c3r2;
	float	c3r3;
}	t_mat3x3;

t_v3	cross(t_v3 a, t_v3 b);
t_v3	norm(t_v3 vec);
t_v3	vec_add(t_v3 v1, t_v3 v2);
t_v3	vec_sub(t_v3 a, t_v3 b);
t_v3	vec_scale(t_v3 vec, float scale);
float	dot(t_v3 a, t_v3 b);
float	len(t_v3 vec);
t_v3	calc_sp_norm(t_v3 ray, t_sp *sp, t_v3 cam_pos, float dst);
t_v3	rot_x(t_v3 vec, float angle);
t_v3	rot_y(t_v3 vec, float angle);
t_v3	rot_z(t_v3 vec, float angle);

#endif
