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

# include "Color.h"
#include "Scene.h"
# include "Vec.h"

# include <stdbool.h>

typedef struct s_img	t_img;
typedef struct s_sc		t_sc;
typedef struct s_mrt	t_mrt;
typedef union u_sh		t_sh;

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
	t_type	type;
	void	*sh;
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
void	render_frame(t_img *img, int rbs, t_mrt *mrt);
void	render_line(t_img *img, int rbs, t_mrt *mrt, int line);
bool	haslight(t_hit *hit, t_sc *sc);
int		calc_color(t_co col, float factor, t_sc *sc);
bool	hit_sh(t_v3 ray, t_sc *sc, t_v3 pos);
bool	hit_shcn(t_v3 ray, t_cn *cn, t_v3 cam_pos, t_li *li);
bool	hit_shbase(t_v3 ray, t_cl *cl, t_v3 cam_pos, float llen);
void	eval_hit_color(t_hit *hit, t_sc *sc);

#endif
