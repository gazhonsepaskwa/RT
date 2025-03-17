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

# include "Vec.h"
# include "Material.h"

typedef struct s_sc t_sc;
typedef struct s_hit t_hit;

typedef struct s_pl
{
	t_v3	pt;
	t_v3	norm;
	t_mat	ma;
	int		col;
}	t_pl;

t_pl	*init_plane(char **arg);
int	add_light_pl(t_pl *pl, t_sc *sc, t_hit *hit);

#endif
