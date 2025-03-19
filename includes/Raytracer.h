/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:33:25 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:33:25 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

#include "Color.h"
# include "Vec.h"
# include "mlx_addon.h"
# include <stdbool.h>

typedef struct s_sc t_sc;

typedef struct s_hit
{
	t_v3	ray;
	t_v3	r_ray;
	t_v3	ori;
	t_v3	norm;
	t_v3	ref;
	bool	hit;
	float	dst;
	int		color;
	t_co	col;
}	t_hit;

typedef struct s_poly
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	x1;
	float	x2;
	float	sol;
}	t_poly;

t_hit	init_hit(t_v3 ray, t_v3 cam_pos);
void	render_frame(t_sc *sc, t_img *img, int rbs);
bool	hasLight(t_hit *hit, t_sc *sc);
int		calc_color(t_co col, float factor);

#endif
