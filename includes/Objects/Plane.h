/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:44:50 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/13 11:44:50 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../Material.h"
# include "../texture.h"
# include "../Color.h"
# include "../Vec.h"

typedef struct s_hit	t_hit;
typedef struct s_sc		t_sc;

typedef struct s_pl
{
	t_v3		pt;
	t_v3		norm;
	t_v3		x;
	t_v3		y;
	t_mat		ma;
	t_co		col;
	t_texture	tex;
}	t_pl;

t_pl	*init_plane(char **arg, void *xsrv);
int		add_light_pl(t_pl *pl, t_sc *sc, t_hit *hit);
void	eval_color_plane(t_hit *hit, t_sc *sc, t_pl *pl);

#endif
