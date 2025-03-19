/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:15:48 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/19 02:15:48 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Raytracer.h"
#include "../../includes/Plane.h"

static int get_color(int x, int y, t_img *texture)
{
	int	px_s;

	px_s = (y * texture->line_len + x * (texture->bpp / 8));
	return (get_rgb(texture->addr[px_s],
				 texture->addr[px_s + 1],
				 texture->addr[px_s + 2]));
}

# include <stdio.h>
int get_pl_texture_color(t_pl *pl, t_hit hit)
{
	float	u;
	float	v;
	int		tex_x;
	int		tex_y;

	u = dot(vec_sub(hit.ori, pl->pt), pl->x);
	v = dot(vec_sub(hit.ori, pl->pt), pl->y);

	tex_x = (int)(fmod(u, 1.0) * pl->tex.b.width);
	tex_y = (int)(fmod(v, 1.0) * pl->tex.b.height);

	tex_x = (tex_x + pl->tex.b.width) % pl->tex.b.width;
	tex_y = (tex_y + pl->tex.b.height) % pl->tex.b.height;

	// printf("u: %f, v: %f\n", u, v);
	// printf("tex_x: %d, tex_y: %d\n", tex_x, tex_y);
	// printf("Color: %d\n", get_color(tex_x, tex_y, &pl->tex.b));
	return get_color(tex_x, tex_y, &pl->tex.b);
}
