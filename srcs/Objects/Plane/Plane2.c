/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:37:58 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 11:37:58 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Plane.h"
#include "../../../includes/Objects/Light.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/Scene.h"
#include "../../../lib/libft/libft.h"

void	eval_color_plane(t_hit *hit, t_sc *sc, t_pl *pl)
{
	if (pl->tex.existb)
		pl->col = get_pl_texture_color(pl, *hit);
	// if (haslight(hit, sc))
	hit->color = add_light_pl(pl, sc, hit);
	// else
	// 	hit->color = calc_color(pl->col, pl->ma.ka, sc);
}

// int	add_light_pl(t_pl *pl, t_sc *sc, t_hit *hit)
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
// 	coeff = pow(fmax(dot(to_li, hit->ref), 0.0f), pl->ma.n);
// 	col[0] = pl-> col.r * pl->ma.ka * sc->li * sc->col.r
// 		+ pl->ma.kd * pl->col.r
// 		* li->col.r * theta + pl->ma.ks * pl->col.r * li->col.r * coeff;
// 	col[1] = pl-> col.g * pl->ma.ka * sc->li * sc->col.g
// 		+ pl->ma.kd * pl->col.g
// 		* li->col.g * theta + pl->ma.ks * pl->col.g * li->col.g * coeff;
// 	col[2] = pl-> col.b * pl->ma.ka * sc->li * sc->col.b
// 		+ pl->ma.kd * pl->col.b
// 		* li->col.b * theta + pl->ma.ks * pl->col.b * li->col.b * coeff;
// 	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
// 	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
// 	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
// 	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
// }

static void	add_colorpl(float	col[5], t_li *li, t_pl *pl)
{
	col[0] += li->col.r * pl->col.r * li->li * (pl->ma.kd * col[4] + pl->ma.ks * col[3]);
	col[1] += li->col.g * pl->col.g * li->li * (pl->ma.kd * col[4] + pl->ma.ks * col[3]);
	col[2] += li->col.b * pl->col.b * li->li * (pl->ma.kd * col[4] + pl->ma.ks * col[3]);
}

int	add_light_pl(t_pl *pl, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	to_li;
	int		i;
	float	col[5];

	i = -1;
	ft_memset(&col, 0, sizeof(float) * 5);
	col[0] = pl->col.r * pl->ma.ka * sc->li * sc->col.r;
	col[1] = pl->col.g * pl->ma.ka * sc->li * sc->col.g;
	col[2] = pl->col.b * pl->ma.ka * sc->li * sc->col.b;
	while (++i < sc->nb_lig)
	{
		li = sc->lig[i];
		to_li = norm(vec_sub(li->pos, hit->ori));
		if (dot(to_li, hit->norm) < 0 || hit_sh(to_li, sc, hit->ori, li))
			continue ;
		col[3] = pow(fmax(dot(to_li, hit->ref), 0.0f), pl->ma.n);
		col[4] = fmax(dot(to_li, hit->norm), 0.0);
		add_colorpl(col, li, pl);
	}
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}
