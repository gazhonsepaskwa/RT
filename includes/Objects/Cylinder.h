/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:06:29 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 16:30:31 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "../Material.h"
# include "../Color.h"
# include "../Vec.h"

typedef struct s_hit	t_hit;
typedef struct s_poly	t_poly;
typedef struct s_sc		t_sc;

typedef struct s_cl
{
	t_v3	pos;
	t_v3	norm;
	t_v3	fw;
	t_v3	ri;
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
	t_v3	b1;
	t_v3	rb1;
	t_v3	i1;
	t_v3	ip1;
	float	ch1;
	float	len1;
	t_v3	b2;
	t_v3	rb2;
	t_v3	i2;
	t_v3	ip2;
	float	ch2;
	float	len2;
}			t_baseop;

t_hit	draw_cl(t_hit tmp, t_cl *cl, t_v3 cam_pos);
t_cl	*init_cl(char **arg);
int		add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit);
void	eval_color_cl(t_hit *hit, t_sc *sc, t_cl *cl);
t_mat	init_macl(char **arg);
void	baseop_op(t_opcl *op, t_hit tmp, t_v3 cam_pos, t_cl *cl);
void	update_bcldhit(t_hit *hit, t_cl *cl, t_baseop b);
void	update_bcluphit(t_hit *hit, t_cl *cl, t_baseop b);
void	update_bcl2hit(t_hit *hit, t_cl *cl, t_baseop b);
void	update_hitcl(t_hit *hit, t_poly p, t_cl *cl);
void	calc_hit_top(t_baseop b, t_hit *hit, t_cl *cl);
void	calc_hit_both(t_baseop b, t_v3 cam, t_cl *cl, t_hit *hit);

#endif
