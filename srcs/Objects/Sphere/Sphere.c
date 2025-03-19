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

// t_v3	rand_pt(t_li *sp)
// {
// 	t_v3	ret;
// 	float	theta;
// 	float	phi;
// 	float	x;
// 	float	y;
//
// 	x = (float)rand() / 2147483647.0f;
// 	y = (float)rand() / 2147483647.0f;
// 	theta = 2.0 * M_PI * x;
// 	phi = acos(2.0 * y - 1.0);
// 	ret.x = sp->r * sin(phi) * cos(theta);
// 	ret.y = sp->r / 2.0f * sin(phi) * sin(theta);
// 	ret.z = sp->r / 2.0f * cos(phi);
// 	ret.x = sp->pos.x + ret.x;
// 	ret.y = sp->pos.y + ret.y;
// 	ret.z = sp->pos.z + ret.z;
// 	return (ret);
// }



int add_light_sp(t_sp *sp, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	double	theta;
	float	col[3];

	li = getLight(sc);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	theta = dot(toLi, hit->norm);
	col[0] = hit->col.r * (sp->col.r * sp->ma.ka * sc->li + sp->ma.kd * li->li * (sp->col.r * li->col.r)  * fmax(theta, 0.0f) + sp->ma.ks * li->li * (sp->col.r * li->col.r)  * pow(fmax(dot(toLi, hit->ref), 0.0f), sp->ma.n)); 
	col[1] = hit->col.g * (sp->col.g * sp->ma.ka * sc->li + sp->ma.kd * li->li * (sp->col.g * li->col.g)  * fmax(theta, 0.0f) + sp->ma.ks * li->li * (sp->col.g * li->col.g)  * pow(fmax(dot(toLi, hit->ref), 0.0f), sp->ma.n)); 
	col[2] = hit->col.b * (sp->col.b * sp->ma.ka * sc->li + sp->ma.kd * li->li * (sp->col.b * li->col.b)  * fmax(theta, 0.0f) + sp->ma.ks * li->li * (sp->col.b * li->col.b)  * pow(fmax(dot(toLi, hit->ref), 0.0f), sp->ma.n)); 
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
	// return (calc_color(sp->ma.col, sp->ma.ka * sc->li + sp->ma.kd * li->li * fmax(theta, 0.0f) + sp->ma.ks *  li->li * pow(fmax(dot(toLi, hit->ref), 0.0f), sp->ma.n)));
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
