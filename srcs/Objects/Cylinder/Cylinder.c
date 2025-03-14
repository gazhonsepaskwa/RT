/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:08:39 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/14 09:08:39 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/libft.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/Cylinder.h"
#include "../../../includes/Scene.h"

static t_v3	init_pt(char **arg)
{
	t_v3	res;

	res.x = ft_atof(arg[0]);
	res.y = ft_atof(arg[1]);
	res.z = ft_atof(arg[2]);
	return (res);
}

int	add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	double	theta;

	li = getLight(sc);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	theta = acos(dot(toLi, hit->norm));
	return (calc_color(cl->col, li->li * cos(theta)));
}

t_cl	*init_cl(char **arg)
{
	t_cl	*cl;
	char	**split;

	cl = malloc(sizeof(t_cl) * 1);
	if (!cl)
		return (NULL);
	split = ft_split(arg[1], ",");
	if (!split)
		return (free(cl), NULL);
	cl->pos = init_pt(split);
	free_tab(split);
	split = ft_split(arg[2], ",");
	if (!split)
		return (free(cl), NULL);
	cl->norm = init_pt(split);
	free_tab(split);
	cl->r = ft_atof(arg[3]) / 2.0f;
	cl->h = ft_atof(arg[4]);
	split = ft_split(arg[5], ",");
	if (!split)
		return(free(cl), NULL);
	cl->col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
						ft_atof(split[2]));
	free_tab(split);
	return (cl);
}
