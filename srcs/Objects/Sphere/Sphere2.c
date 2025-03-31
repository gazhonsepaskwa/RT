/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:56 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 12:13:56 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Sphere.h"
#include "../../../includes/Raytracer.h"
#include "../../../includes/texture.h"
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

static void	update_hit(t_v3 ray, t_hit *hit, t_v3 cam_pos, t_sp *sp)
{
	hit->hit = true;
	hit->ori = vec_add(cam_pos, vec_scale(ray, hit->dst));
	hit->norm = calc_sp_norm(ray, sp, cam_pos, hit->dst);
	if (sp->tex.existn)
		hit->norm = get_sp_nmap_vec(sp, *hit);
	hit->ref = vec_sub(ray, vec_scale(hit->norm, 2 * dot(ray, hit->norm)));
	hit->ref = norm(hit->ref);
	hit->r_ray = vec_scale(ray, -1);
	hit->sh = sp;
	hit->type = SPHERE;
}

t_hit	draw_sp(t_hit tmp, t_sp *sp, t_v3 cam_pos)
{
	t_poly	p;
	t_hit	hit;
	t_v3	oc;

	hit = init_hit(tmp.ray, cam_pos);
	oc = vec_sub(cam_pos, sp->pos);
	p.a = dot(tmp.ray, tmp.ray);
	p.b = 2.0f * dot(oc, tmp.ray);
	p.c = dot(oc, oc) - (sp->dia * 0.5 * sp->dia * 0.5);
	p.delta = p.b * p.b - 4 * p.a * p.c;
	if (p.delta >= 0)
	{
		hit.dst = fminpos((-p.b + sqrt(p.delta)) / (2.0f * p.a),
				(-p.b - sqrt(p.delta)) / (2.0f * p.a));
		if (hit.dst >= 0 && (!tmp.hit || (tmp.dst > 0 && hit.dst < tmp.dst)))
			update_hit(tmp.ray, &hit, cam_pos, sp);
	}
	return (hit);
}

static void	add_colorsp(float	col[5], t_li *li, t_sp *sp)
{
	col[0] += li->col.r * sp->col.r * (sp->ma.kd * col[4] + sp->ma.ks * col[3]);
	col[1] += li->col.g * sp->col.g * (sp->ma.kd * col[4] + sp->ma.ks * col[3]);
	col[2] += li->col.b * sp->col.b * (sp->ma.kd * col[4] + sp->ma.ks * col[3]);
}

int	add_light_sp(t_sp *sp, t_sc *sc, t_hit *hit)
{
	t_li	*li;
	t_v3	to_li;
	int		i;
	float	col[5];

	i = -1;
	ft_memset(&col, 0, sizeof(float) * 5);
	col[0] = sp->col.r * sp->ma.ka * sc->li * sc->col.r;
	col[1] = sp->col.g * sp->ma.ka * sc->li * sc->col.g;
	col[2] = sp->col.b * sp->ma.ka * sc->li * sc->col.b;
	while (++i < sc->nb_lig)
	{
		li = sc->lig[i];
		to_li = norm(vec_sub(li->pos, hit->ori));
		if (dot(to_li, hit->norm) < 0 || hit_sh(to_li, sc, hit->ori, li))
			continue ;
		col[3] = pow(fmax(dot(to_li, hit->ref), 0.0f), sp->ma.n);
		col[4] = fmax(dot(to_li, hit->norm), 0.0);
		add_colorsp(col, li, sp);
	}
	col[0] = clump(col[0], 0.0f, 1.0f) * 255;
	col[1] = clump(col[1], 0.0f, 1.0f) * 255;
	col[2] = clump(col[2], 0.0f, 1.0f) * 255;
	return ((int)col[0] << 16 | (int)col[1] << 8 | (int)col[2]);
}
