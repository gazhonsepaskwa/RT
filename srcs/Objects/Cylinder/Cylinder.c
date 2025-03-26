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

#include "../../../includes/Objects/Cylinder.h"
#include "../../../includes/mlx_addon.h"
#include "../../../includes/Raytracer.h"
#include "../../../lib/libft/libft.h"

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else
		return (fmin(a, b));
}

static t_v3	init_pt(char **arg)
{
	t_v3	res;

	res.x = ft_atof(arg[0]);
	res.y = ft_atof(arg[1]);
	res.z = ft_atof(arg[2]);
	free_tab(arg);
	return (res);
}

static	void	hit_base(t_hit *hit, t_cl *cl, t_v3	cam)
{
	t_opcl		op;
	t_baseop	b;

	op.oc = vec_scale(cl->norm, cl->h / 2);
	b.b1 = vec_add(cl->pos, op.oc);
	b.b2 = vec_sub(cl->pos, op.oc);
	b.rb1 = vec_sub(b.b1, cam);
	b.rb2 = vec_sub(b.b2, cam);
	b.ch1 = dot(b.rb1, cl->norm) / dot(hit->ray, cl->norm);
	b.ch2 = dot(b.rb2, cl->norm) / dot(hit->ray, cl->norm);
	if (b.ch1 > 0 && b.ch2 > 0)
		calc_hit_both(b, cam, cl, hit);
	else if (b.ch1 > 0 && b.ch2 < 0)
		calc_hit_top(b, hit, cl);
	else if (b.ch1 < 0 && b.ch2 > 0)
	{
		b.i2 = vec_add(hit->ori, vec_scale(hit->ray, b.ch2));
		b.ip2 = vec_sub(b.i2, b.b2);
		b.len2 = sqrt(b.ip2.x * b.ip2.x + b.ip2.y
				* b.ip2.y + b.ip2.z * b.ip2.z);
		if (b.len2 <= cl->r)
			return (update_bcldhit(hit, cl, b));
	}
}

t_hit	draw_cl(t_hit tmp, t_cl *cl, t_v3 cam_pos)
{
	t_hit	hit;
	t_poly	p;
	t_opcl	op;
	float	h;

	hit = init_hit(tmp.ray, cam_pos);
	baseop_op(&op, tmp, cam_pos, cl);
	p.a = dot(op.r_p, op.r_p);
	p.b = 2.0f * dot(op.oc_p, op.r_p);
	p.c = dot(op.oc_p, op.oc_p) - cl->r * cl->r;
	p.delta = p.b * p.b - 4.0f * p.a * p.c;
	if (p.delta < 0)
		return (hit);
	p.x1 = (-p.b + sqrt(p.delta)) / (2.0f * p.a);
	p.x2 = (-p.b - sqrt(p.delta)) / (2.0f * p.a);
	p.sol = fminpos(p.x1, p.x2);
	if (p.sol < 0)
		return (hit);
	op.pt = vec_add(cam_pos, vec_scale(tmp.ray, p.sol));
	h = dot(vec_sub(op.pt, cl->pos), cl->norm);
	if (fabs(h) <= cl->h / 2 && (!tmp.hit || (tmp.dst > 0 && p.sol < tmp.dst)))
		update_hitcl(&hit, p, cl);
	if (!hit.hit)
		hit_base(&hit, cl, cam_pos);
	return (hit);
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
	split = ft_split(arg[2], ",");
	if (!split)
		return (free(cl), NULL);
	cl->norm = norm(init_pt(split));
	initaxis(cl->norm, &cl->fw, &cl->ri);
	cl->r = ft_atof(arg[3]) / 2.0f;
	cl->h = ft_atof(arg[4]);
	split = ft_split(arg[5], ",");
	if (!split)
		return (free(cl), NULL);
	cl->ma.col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	cl->col = init_color(split);
	cl->ma = init_macl(arg);
	free_tab(split);
	return (cl);
}
