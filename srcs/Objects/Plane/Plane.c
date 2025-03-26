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

#include "../../../includes/Objects/Plane.h"
#include "../../../includes/Objects/Light.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/Raytracer.h"
#include "../../../lib/libft/libft.h"
#include "../../../includes/Vec.h"

static t_v3	init_pt(char **arg)
{
	t_v3	res;

	res.x = ft_atof(arg[0]);
	res.y = ft_atof(arg[1]);
	res.z = ft_atof(arg[2]);
	free_tab(arg);
	return (res);
}

static	t_mat	init_mapl(char **arg, char **split)
{
	t_mat	ma;

	ma.ka = ft_atof(arg[4]);
	ma.kd = ft_atof(arg[5]);
	ma.ks = ft_atof(arg[6]);
	ma.n = ft_atof(arg[7]);
	ma.col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	return (ma);
}

t_hit	draw_pl(t_hit tmp, t_pl *pl, t_v3 cam_pos)
{
	t_hit	hit;
	float	dist;

	hit = init_hit(tmp.ray, cam_pos);
	if (dot(tmp.ray, pl->norm) == 0.0f)
		return (hit);
	dist = -(dot(vec_sub(cam_pos, pl->pt), pl->norm)) / dot(tmp.ray, pl->norm);
	if (dist > 0 && (!tmp.hit || (tmp.dst > 0 && dist < tmp.dst)))
	{
		hit.dst = dist;
		hit.hit = true;
		hit.ori = vec_add(cam_pos, vec_scale(tmp.ray, hit.dst));
		if (dot(tmp.ray, pl->norm) < 0)
			hit.norm = pl->norm;
		else
			hit.norm = vec_scale(pl->norm, -1.0);
		if (pl->tex.existn)
			hit.norm = get_pl_nmap_vec(pl, hit);
		hit.ref = vec_sub(tmp.ray, vec_scale(hit.norm,
					2 * dot(tmp.ray, hit.norm)));
		hit.ref = norm(hit.ref);
		hit.sh = pl;
		hit.type = PLANE;
	}
	return (hit);
}

t_pl	*init_plane(char **arg, void *xsrv)
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
	split = ft_split(arg[2], ",");
	if (!split)
		return (free(pl), NULL);
	pl->norm = init_pt(split);
	split = ft_split(arg[3], ",");
	if (!split)
		return (free(pl), NULL);
	pl->ma = init_mapl(arg, split);
	pl->col = init_color(split);
	free_tab(split);
	initaxis(pl->norm, &pl->x, &pl->y);
	init_texture(&pl->tex, xsrv, arg[8]);
	return (pl);
}
