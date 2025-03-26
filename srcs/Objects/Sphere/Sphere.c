/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:16:26 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:16:26 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Sphere.h"
#include "../../../includes/Objects/Light.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/texture.h"
#include "../../../lib/libft/libft.h"
#include "../../../includes/Scene.h"

static	t_v3	init_pos(char **split)
{
	t_v3	pos;

	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	return (pos);
}

void	eval_color_sp(t_hit *hit, t_sc *sc, t_sp *sp)
{
	if (sp->tex.existb)
		sp->col = get_sp_texture_color(sp, *hit);
	if (hasLight(hit, sc))
		hit->color = add_light_sp(sp, sc, hit);
	else
		hit->color = calc_color(sp->col, sp->ma.ka, sc);
}

int add_light_sp(t_sp *sp, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	double	theta;
	float	coeff;
	float	col[3];

	li = getLight(sc);
	toLi = vec_sub(li->pos, hit->ori);
	toLi = norm(toLi);
	coeff = pow(fmax(dot(toLi, hit->ref), 0.00000f), sp->ma.n);
	theta = dot(toLi, hit->norm);
	theta = fmax(theta- 0.1, 0.0);
	col[0] = (sp->col.r * sp->ma.ka * sc->li * sc->col.r + sp->ma.kd * (sp->col.r * 
		li->col.r) * theta + sp->ma.ks * (sp->col.r * li->col.r) * coeff); 
	col[1] = (sp->col.g * sp->ma.ka * sc->li * sc->col.g + sp->ma.kd * (sp->col.g * 
		li->col.g) * theta + sp->ma.ks * (sp->col.g * li->col.g) * coeff); 
	col[2] = (sp->col.b * sp->ma.ka * sc->li *sc->col.b + sp->ma.kd * (sp->col.b *
		li->col.b) * theta + sp->ma.ks * (sp->col.b * li->col.b) * coeff); 
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}

t_sp	*init_sphere(char **args, void *xsrv)
{
	t_sp	*sp;
	char	**split;

	sp = malloc(sizeof(t_sp) * 1);
	if (!sp)
		return (NULL);
	split = ft_split(args[1], ",");
	if (!split)
		return(free(sp), NULL);
	sp->pos = init_pos(split);
	free_tab(split);
	sp->dia = ft_atof(args[2]);
	split = ft_split(args[3], ",");
	if (!split)
		return(free(sp), NULL);
	sp->ma.col = col_from_rgb(ft_atof(split[0]),
							ft_atof(split[1]),
							ft_atof(split[2]));
	sp->col = init_color(split);
	sp->ma.ka = ft_atof(args[4]);
	sp->ma.kd = ft_atof(args[5]);
	sp->ma.ks = ft_atof(args[6]);
	sp->ma.n = ft_atof(args[7]);
	sp->up = (t_v3){0, 1, 0, 0, 0};
	sp->ri = norm(cross((t_v3){0, 0, 1, 0, 0}, sp->up));
	if (len(sp->ri) < 0.001f)
		sp->ri = (t_v3){1, 0, 0, 0, 0};
	sp->fw = cross(sp->up, sp->ri);
	init_texture(&sp->tex, xsrv, args[8]);
	free_tab(split);
	return (sp);
}
