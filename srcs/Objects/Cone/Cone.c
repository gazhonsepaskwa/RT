/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:07:20 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/24 12:31:18 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Cone.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/Raytracer.h"
#include "../../../lib/libft/libft.h"
#include "../../../includes/Scene.h"

#include <stdio.h>
static t_v3	init_pt(char **arg)
{
	t_v3	res;

	res.x = ft_atof(arg[0]);
	res.y = ft_atof(arg[1]);
	res.z = ft_atof(arg[2]);
	return (res);
}

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else return fmin(a, b);
}

static	void	update_hitcn(t_hit *hit, t_cn *cn)
{
	t_v3	oc;
	float	tmp;

	hit->hit = true;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	// oc = vec_sub(cn->pos, hit->ori);
	oc = vec_sub(hit->ori, cn->pos);
	tmp = dot(oc, cn->norm);
	hit->norm = vec_sub(vec_scale(cn->norm, 2.0*tmp), vec_scale(oc, 2.0*powf(cos(M_PI/9), 2)));
	hit->norm = norm(hit->norm);
	hit->norm = vec_scale(hit->norm, -1.0);
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm, 2.0*dot(hit->ray, hit->norm)));
}

int	add_light_cn(t_cn *cn, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	toLi;
	double	theta;
	float	coeff;
	float	col[3];

	li = getLight(sc);
	toLi = vec_sub(li->pos, vec_add(hit->ori, vec_scale(hit->norm, 0.01f)));
	toLi = norm(toLi);
	coeff = pow(fmax(dot(toLi, hit->ref), 0.0f), cn->ma.n);
	theta = dot(toLi, hit->norm);
	theta = fmax(theta- 0.1, 0.0);
	col[0] = (cn->col.r * cn->ma.ka * sc->li * sc->col.r + cn->ma.kd * cn->col.r * 
		li->col.r * theta + cn->ma.ks * cn->col.r * li->col.r * coeff); 
	col[1] = (cn->col.g * cn->ma.ka * sc->li * sc->col.g + cn->ma.kd * cn->col.g * 
		li->col.g * theta + cn->ma.ks * cn->col.g * li->col.g * coeff); 
	col[2] = (cn->col.b * cn->ma.ka * sc->li * sc->col.b + cn->ma.kd * cn->col.b * 
		li->col.b * theta + cn->ma.ks * cn->col.b * li->col.b * coeff); 
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}

t_hit	draw_cn(t_v3 ray, t_cn *cn, t_v3 cam_pos, t_sc *sc)
{
	t_hit	hit;
	t_v3	oc;
	t_poly p;

	hit = init_hit(ray, cam_pos);
	oc = vec_sub(cam_pos, cn->pos);
	p.a = powf(dot(ray, cn->norm), 2) - powf(cos(M_PI / 9), 2);
	p.b = 2.0 * (dot(ray, cn->norm) * dot(oc, cn->norm) - powf(cos(M_PI / 9), 2) * dot(ray, oc));
	p.c = powf(dot(oc, cn->norm), 2) - powf(cos(M_PI / 9), 2) * dot(oc, oc);
	p.delta = p.b*p.b - 4.0 * p.a * p.c;
	if (p.delta < 0)
		return (hit);
	hit.dst = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a), (-p.b - sqrt(p.delta)) / (2.0f * p.a));
	if (hit.dst <= 0)
		return (hit);
	update_hitcn(&hit, cn);
	if (hasLight(&hit, sc))
		hit.color = add_light_cn(cn, sc, &hit);
	else
		hit.color = calc_color(cn->col, cn->ma.ka, sc);
	return (hit);
}

t_cn	*init_cn(char **arg)
{
	t_cn	*cn;
	char	**split;

	cn = malloc(sizeof(t_cn) * 1);
	if (!cn)
		return (NULL);
	split = ft_split(arg[1], ",");
	if (!split)
		return(free(cn), NULL);
	cn->pos = init_pt(split);
	free_tab(split);
	split = ft_split(arg[2], ",");
	if (!split)
		return (free(cn), NULL);
	cn->norm = init_pt(split);
	free_tab(split);
	split = ft_split(arg[3], ",");
	if (!split)
		return (free(cn), NULL);
	cn->ma.col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
						   ft_atof(split[2]));
	cn->col = init_color(split);
	free_tab(split);
	cn->ma.ka = ft_atof(arg[4]);
	cn->ma.kd = ft_atof(arg[5]);
	cn->ma.ks = ft_atof(arg[6]);
	cn->ma.n = ft_atof(arg[7]);
	return (cn);
}
