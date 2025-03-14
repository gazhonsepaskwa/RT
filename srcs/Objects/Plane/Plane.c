/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:44:45 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/13 11:44:45 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Plane.h"
#include "../../../includes/Scene.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/mlx_addon.h"
#include "../../../lib/libft/libft.h"


static t_v3	init_pt(char **arg)
{
	t_v3	res;

	res.x = ft_atof(arg[0]);
	res.y = ft_atof(arg[1]);
	res.z = ft_atof(arg[2]);
	return (res);
}

#include <stdio.h>
int	add_light_pl(t_pl *pl, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	t_v3	r_li;
	double	theta;

	li = getLight(sc);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	theta = dot(toLi, hit->norm);
	r_li = vec_sub(toLi, vec_scale(hit->norm, 2 * dot(toLi, hit->norm)));
	return (calc_color(pl->col, sc->li + li->li * fmax(theta, 0.01f) + 0.3 * li->li * pow(fmax(dot(toLi, hit->ref), 0.0f), 51)));
}

t_pl	*init_plane(char **arg)
{
	t_pl	*pl;
	char	**split;

	pl = malloc(sizeof(t_pl) * 1);
	if (!pl)
		return (NULL);
	split = ft_split(arg[1], ",");
	if (!split)
		return (free(pl), NULL);
	pl->pt = init_pt(split);
	free_tab(split);
	split = ft_split(arg[2], ",");
	if (!split)
		return (free(pl), NULL);
	pl->norm = init_pt(split);
	free_tab(split);
	split = ft_split(arg[3], ",");
	if (!split)
		return (free(pl), NULL);
	pl->col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
						ft_atof(split[2]));
	free_tab(split);
	return (pl);
}
