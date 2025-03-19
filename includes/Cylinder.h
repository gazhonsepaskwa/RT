/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:06:29 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/14 09:06:29 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

#include "Color.h"
# include "Material.h"
# include "Vec.h"

typedef struct s_sc t_sc;
typedef struct s_hit t_hit;

typedef struct s_cl
{
	t_v3	pos;
	t_v3	norm;
	float	h;
	float	r;
	t_mat	ma;
	t_co	col;
}	t_cl;

typedef struct s_opcl
{
	t_v3	oc;
	t_v3	r_p;
	t_v3	oc_p;
	t_v3	pt;
}	t_opcl;

typedef struct s_baseop
{
	t_v3 	b1;
	t_v3 	rb1;
	t_v3	i1;
	t_v3	ip1;
	float	ch1;
	float	len1;
	t_v3	b2;
	t_v3	rb2;
	t_v3	i2;
	t_v3 	ip2;
	float	ch2;
	float	len2;
}	t_baseop;

t_cl	*init_cl(char **arg);
int	add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit);
t_hit	draw_cl(t_v3 ray, t_cl *cl, t_v3 cam_pos, t_sc *sc);

#endif
