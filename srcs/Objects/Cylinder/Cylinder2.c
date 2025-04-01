/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:03:12 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 11:03:12 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cylinder.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/Raytracer.h"
#include "../../../lib/libft/libft.h"
#include "../../../includes/Scene.h"

void	eval_color_cl(t_hit *hit, t_sc *sc, t_cl *cl)
{
	// if (haslight(hit, sc))
	hit->color = add_light_cl(cl, sc, hit);
	// else
		// hit->color = calc_color(cl->col, cl->ma.ka, sc);
}

// int	add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit)
// {
// 	t_li	*li;
// 	t_v3	to_li;
// 	double	theta;
// 	float	col[3];
// 	float	coeff;
//
// 	li = getlight(sc);
// 	to_li = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
// 	to_li = norm(to_li);
// 	theta = dot(to_li, hit->norm);
// 	theta = fmax(theta - 0.1, 0.0);
// 	coeff = pow(fmax(dot(to_li, hit->ref), 0.0f), cl->ma.n);
// 	col[0] = cl->col.r * cl->ma.ka * sc->li * sc->col.r
// 		+ cl->ma.kd * cl->col.r
// 		* li->col.r * theta + cl->ma.ks * cl->col.r * li->col.r * coeff;
// 	col[1] = cl->col.g * cl->ma.ka * sc->li * sc->col.g
// 		+ cl->ma.kd * cl->col.g
// 		* li->col.g * theta + cl->ma.ks * cl->col.g * li->col.g * coeff;
// 	col[2] = cl->col.b * cl->ma.ka * sc->li * sc->col.b
// 		+ cl->ma.kd * cl->col.b
// 		* li->col.b * theta + cl->ma.ks * cl->col.b * li->col.b * coeff;
// 	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
// 	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
// 	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
// 	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
// }

t_mat	init_macl(char **arg)
{
	t_mat	ma;

	ma.ka = ft_atof(arg[6]);
	ma.kd = ft_atof(arg[7]);
	ma.ks = ft_atof(arg[8]);
	ma.n = ft_atof(arg[9]);
	return (ma);
}

void	baseop_op(t_opcl *op, t_hit tmp, t_v3 cam_pos, t_cl *cl)
{
	op->oc = vec_sub(cam_pos, cl->pos);
	op->r_p = vec_sub(tmp.ray, vec_scale(cl->norm, dot(cl->norm, tmp.ray)));
	op->oc_p = vec_sub(op->oc, vec_scale(cl->norm, dot(cl->norm, op->oc)));
}

static void	add_colorcl(float	col[5], t_li *li, t_cl *cl)
{
	col[0] += li->col.r * cl->col.r * li->li * (cl->ma.kd * col[4] + cl->ma.ks * col[3]);
	col[1] += li->col.g * cl->col.g * li->li  * (cl->ma.kd * col[4] + cl->ma.ks * col[3]);
	col[2] += li->col.b * cl->col.b * li->li * (cl->ma.kd * col[4] + cl->ma.ks * col[3]);
}

int	add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	to_li;
	int		i;
	float	col[5];

	i = -1;
	ft_memset(&col, 0, sizeof(float) * 5);
	col[0] = cl->col.r * cl->ma.ka * sc->li * sc->col.r;
	col[1] = cl->col.g * cl->ma.ka * sc->li * sc->col.g;
	col[2] = cl->col.b * cl->ma.ka * sc->li * sc->col.b;
	while (++i < sc->nb_lig)
	{
		li = sc->lig[i];
		to_li = norm(vec_sub(li->pos, hit->ori));
		if (dot(to_li, hit->norm) < 0 || hit_sh(to_li, sc, hit->ori, li))
			continue ;
		col[3] = pow(fmax(dot(to_li, hit->ref), 0.0f), cl->ma.n);
		col[4] = fmax(dot(to_li, hit->norm), 0.0);
		add_colorcl(col, li, cl);
	}
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}
