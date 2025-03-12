/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:33:25 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/12 08:33:25 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "Scene.h"
# include "Vec.h"
# include "mlx_addon.h"
# include <stdbool.h>

typedef struct s_hit
{
	t_v3	ray;
	t_v3	norm;
	bool	hit;
	float	dst;
	int		color;
}	t_hit;

typedef struct s_poly
{
	float	a;
	float	b;
	float	c;
	float	delta;
}	t_poly;

void	raytrace(t_sc *sc, t_img *img);
t_hit	init_hit(t_v3 ray);

#endif
