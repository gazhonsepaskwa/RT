/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:36 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 10:52:36 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cone.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/Scene.h"
#include "../../../lib/libft/libft.h"

// int	add_light_cn(t_cn *cn, t_sc *sc, t_hit *hit)
// {
// 	t_li	*li;
// 	t_v3	to_li;
// 	double	theta;
// 	float	coeff;
// 	float	col[3];
//
// 	li = getlight(sc);
// 	to_li = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
// 	to_li = norm(to_li);
// 	coeff = pow(fmax(dot(to_li, hit->ref), 0.0f), cn->ma.n);
// 	theta = dot(to_li, hit->norm);
// 	theta = fmax(theta - 0.1, 0.0);
// 	col[0] = (cn->col.r * cn->ma.ka * sc->li * sc->col.r
// 			+ cn->ma.kd * cn->col.r
// 			* li->col.r * theta + cn->ma.ks * cn->col.r * li->col.r * coeff);
// 	col[1] = (cn->col.g * cn->ma.ka * sc->li * sc->col.g
// 			+ cn->ma.kd * cn->col.g
// 			* li->col.g * theta + cn->ma.ks * cn->col.g * li->col.g * coeff);
// 	col[2] = (cn->col.b * cn->ma.ka * sc->li * sc->col.b
// 			+ cn->ma.kd * cn->col.b
// 			* li->col.b * theta + cn->ma.ks * cn->col.b * li->col.b * coeff);
// 	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
// 	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
// 	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
// 	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
// }

void	eval_color_cone(t_hit *hit, t_sc *sc, t_cn *cn)
{
	// if (haslight(hit, sc))
	hit->color = add_light_cn(cn, sc, hit);
	// else
		// hit->color = calc_color(cn->col, cn->ma.ka, sc);
}

t_mat	init_macn(char **arg)
{
	t_mat	ma;

	ma.ka = ft_atof(arg[4]);
	ma.kd = ft_atof(arg[5]);
	ma.ks = ft_atof(arg[6]);
	ma.n = ft_atof(arg[7]);
	return (ma);
}

static void	add_colorcn(float	col[5], t_li *li, t_cn *cn)
{
	col[0] += li->col.r * cn->col.r * (cn->ma.kd * col[4] + cn->ma.ks * col[3]);
	col[1] += li->col.g * cn->col.g * (cn->ma.kd * col[4] + cn->ma.ks * col[3]);
	col[2] += li->col.b * cn->col.b * (cn->ma.kd * col[4] + cn->ma.ks * col[3]);
}

int	add_light_cn(t_cn *cn, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	to_li;
	int		i;
	float	col[5];

	i = -1;
	ft_memset(&col, 0, sizeof(float) * 5);
	col[0] = cn->col.r * cn->ma.ka * sc->li * sc->col.r;
	col[1] = cn->col.g * cn->ma.ka * sc->li * sc->col.g;
	col[2] = cn->col.b * cn->ma.ka * sc->li * sc->col.b;
	while (++i < sc->nb_lig)
	{
		li = sc->lig[i];
		to_li = norm(vec_sub(li->pos, hit->ori));
		if (dot(to_li, hit->norm) < 0 || hit_sh(to_li, sc, hit->ori, li))
			continue ;
		col[3] = pow(fmax(dot(to_li, hit->ref), 0.0f), cn->ma.n);
		col[4] = fmax(dot(to_li, hit->norm), 0.0);
		add_colorcn(col, li, cn);
	}
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}
