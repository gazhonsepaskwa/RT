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
	free_tab(split);
	return (pos);
}

void	eval_color_sp(t_hit *hit, t_sc *sc, t_sp *sp)
{
	if (sp->tex.existb)
		sp->col = get_sp_texture_color(sp, *hit);
	hit->color = add_light_sp(sp, sc, hit);
}

static	t_mat	init_masp(char **args, char **split)
{
	t_mat	ma;

	ma.col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ma.ka = ft_atof(args[4]);
	ma.kd = ft_atof(args[5]);
	ma.ks = ft_atof(args[6]);
	ma.n = ft_atof(args[7]);
	return (ma);
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
		return (free(sp), NULL);
	sp->pos = init_pos(split);
	sp->dia = ft_atof(args[2]);
	split = ft_split(args[3], ",");
	if (!split)
		return (free(sp), NULL);
	sp->ma = init_masp(args, split);
	sp->col = init_color(split);
	sp->up = (t_v3){0, 1, 0, 0, 0};
	initaxis(sp->up, &sp->fw, &sp->ri);
	init_texture(&sp->tex, xsrv, args[8]);
	free_tab(split);
	return (sp);
}
