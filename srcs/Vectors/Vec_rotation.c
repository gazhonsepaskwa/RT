/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:04:47 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 14:04:47 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Vec.h"

static t_v3	mult_mat(t_mat3x3 mat, t_v3 p)
{
	t_v3	res;

	res.x = p.x * mat.c1r1 + p.y * mat.c2r1 + p.z * mat.c3r1;
	res.y = p.x * mat.c1r2 + p.y * mat.c2r2 + p.z * mat.c3r2;
	res.z = p.x * mat.c1r3 + p.y * mat.c2r3 + p.z * mat.c3r3;
	return (res);
}

t_v3	rot_x(t_v3 vec, float angle)
{
	t_mat3x3	r_x;

	r_x = (t_mat3x3){
		1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)};
	return (mult_mat(r_x, vec));
}

t_v3	rot_y(t_v3 vec, float angle)
{
	t_mat3x3	r_y;

	r_y = (t_mat3x3){
		cos(angle), 0, sin(angle),
		0, 1, 0,
		-sin(angle), 0, cos(angle)};
	return (mult_mat(r_y, vec));
}

t_v3	rot_z(t_v3 vec, float angle)
{
	t_mat3x3	r_z;

	r_z = (t_mat3x3){
		cos(angle), -sin(angle), 0,
		sin(angle), cos(angle), 0,
		0, 0, 1};
	return (mult_mat(r_z, vec));
}
