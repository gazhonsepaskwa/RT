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

static float	fminpos(float a, float b)
{
	if (a < (float)0)
		return (b);
	else if (b < (float)0)
		return (a);
	else return fmin(a, b);
}

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
	theta = dot(toLi, hit->norm);
	// return (calc_color(cl->ma.col, cl->ma.ka * sc->li + cl->ma.kd * li->li * fmax(theta, 0.0f) + cl->ma.ks * li->li * pow(fmax(dot(toLi, hit->ref), 0.0f), cl->ma.n)));
	return (cl->ma.col);
}

static void	update_hitcl(t_hit *hit, t_poly p, t_cl *cl)
{
	t_v3	oc;
	t_v3	proj;

	hit->hit = true;
	hit->dst = p.sol;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	oc = vec_sub(hit->ori, cl->pos);
	proj = vec_scale(cl->norm, dot(oc, cl->norm));
	hit->norm = norm(vec_sub(oc, proj));
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm, 2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
}

static void	update_bcl2hit(t_hit *hit, t_cl *cl, t_baseop b)
{
	t_v3	tob1;
	t_v3	tob2;
	hit->hit = true;
	hit->dst = b.ch1;
	hit->ori = b.i1;
	tob1 = vec_sub(b.b1, hit->ori);
	tob2 = vec_sub(b.b2, hit->ori);
	if (len(tob1) < len(tob2))
		hit->norm = cl->norm;
	else
		hit->norm = vec_scale(cl->norm, -1);
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm, 2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
}

static void	update_bcluphit(t_hit *hit, t_cl *cl, t_baseop b)
{
	hit->hit =true;
	hit->dst = b.ch1;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	hit->norm = cl->norm;
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm, 2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
}

static void	update_bcldhit(t_hit *hit, t_cl *cl, t_baseop b)
{
	hit->hit =true;
	hit->dst = b.ch2;
	hit->ori = vec_add(hit->ori, vec_scale(hit->ray, hit->dst));
	hit->norm = vec_scale(cl->norm, -1);
	hit->ref = vec_sub(hit->ray, vec_scale(hit->norm, 2 * dot(hit->ray, hit->norm)));
	hit->ref = norm(hit->ref);
}

static	bool	hit_base(t_hit *hit, t_cl *cl, t_v3	cam)
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
	{
		b.i1 = vec_add(cam, vec_scale(hit->ray, b.ch1));
		b.i2 = vec_add(cam, vec_scale(hit->ray, b.ch2));
		if (len(vec_sub(b.i1, cam)) > len(vec_sub(b.i2, cam)))
		{
			b.ch1 = b.ch2;
			b.i1 = b.i2;
			b.b1 = b.b2;
		}
		b.ip1 = vec_sub(b.i1, b.b1);
		b.len1 = sqrt(b.ip1.x * b.ip1.x + b.ip1.y * b.ip1.y + b.ip1.z * b.ip1.z);
		if (b.len1 <= cl->r)
			return (update_bcl2hit(hit, cl, b), true);
	}
	else if (b.ch1 > 0 && b.ch2 < 0)
	{
		b.i1 = vec_add(hit->ori, vec_scale(hit->ray, b.ch1));
		b.ip1 = vec_sub(b.i1, b.b1);
		b.len1 = sqrt(b.ip1.x * b.ip1.x + b.ip1.y * b.ip1.y + b.ip1.z * b.ip1.z);
		if (b.len1 <= cl->r)
			return (update_bcluphit(hit, cl, b), true);
	}
	else if (b.ch1 < 0 && b.ch2 > 0)
	{		
		b.i2 = vec_add(hit->ori, vec_scale(hit->ray, b.ch2));
		b.ip2 = vec_sub(b.i2, b.b2);
		b.len2 = sqrt(b.ip2.x * b.ip2.x + b.ip2.y * b.ip2.y + b.ip2.z * b.ip2.z);
		if (b.len2 <= cl->r)
			return (update_bcldhit(hit, cl, b), true);
	}
	return (false);
}

t_hit	draw_cl(t_v3 ray, t_cl *cl, t_v3 cam_pos, t_sc *sc)
{
	t_hit	hit;
	t_poly	p;
	t_opcl	op;
	float	h;

	hit = init_hit(ray, cam_pos);
	op.oc = vec_sub(cam_pos, cl->pos);
	op.r_p = vec_sub(ray, vec_scale(cl->norm, dot(cl->norm, ray)));
	op.oc_p = vec_sub(op.oc, vec_scale(cl->norm, dot(cl->norm, op.oc)));
	p.a = dot(op.r_p, op.r_p);
	p.b = 2.0f * dot(op.oc_p, op.r_p);
	p.c = dot(op.oc_p, op.oc_p) - cl->r*cl->r;
	p.delta = p.b*p.b - 4.0f * p.a * p.c;
	if (p.delta < 0)
		return (hit);
	p.x1 = (-p.b + sqrt(p.delta)) / (2.0f * p.a);
	p.x2 = (-p.b - sqrt(p.delta)) / (2.0f * p.a);
	p.sol = fminpos(p.x1, p.x2);
	if (p.sol < 0)
		return (hit);
	op.pt = vec_add(cam_pos, vec_scale(ray, p.sol));
	h = dot(vec_sub(op.pt, cl->pos), cl->norm);
	if (fabs(h) <= cl->h / 2)
	{
		update_hitcl(&hit, p, cl);
		if (hasLight(&hit, sc))
			hit.color = add_light_cl(cl, sc, &hit);
		else
			hit.color = cl->ma.col;
			// hit.color = calc_color(cl->ma.col, cl->ma.ka * sc->li);
	}
	if (!hit.hit && hit_base(&hit, cl, cam_pos))
	{
		if (hasLight(&hit, sc))
			hit.color = add_light_cl(cl, sc, &hit);
		else
			hit.color = cl->ma.col;
			// hit.color = calc_color(cl->ma.col, cl->ma.ka * sc->li);
	}
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
	cl->ma.col = col_from_rgb(ft_atof(split[0]), ft_atof(split[1]),
						ft_atof(split[2]));
	cl->ma.ka = ft_atof(arg[6]); 
	cl->ma.kd = ft_atof(arg[7]); 
	cl->ma.ks = ft_atof(arg[8]); 
	cl->ma.n = ft_atof(arg[9]); 
	free_tab(split);
	return (cl);
}
