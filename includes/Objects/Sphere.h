/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 10:14:25 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "../Material.h"
# include "../texture.h"
# include "../Color.h"
# include "../Vec.h"

typedef struct s_li		t_li;
typedef struct s_sc		t_sc;

typedef struct s_sp
{
	t_v3		pos;
	float		dia;
	t_mat		ma;
	t_texture	tex;
	t_v3		up;
	t_v3		ri;
	t_v3		fw;
	t_co		col;
}	t_sp;

t_sp	*init_sphere(char **args, void *xsrv);
t_v3	rand_pt(t_li *sp);
int		add_light_sp(t_sp *sp, t_sc *sc, t_hit *hit);

#endif
