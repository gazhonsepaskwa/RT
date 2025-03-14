/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:06:29 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/14 09:06:29 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "Vec.h"

typedef struct s_sc t_sc;
typedef struct s_hit t_hit;

typedef struct s_cl
{
	t_v3	pos;
	t_v3	norm;
	float	h;
	float	r;
	int		col;
}	t_cl;

typedef struct s_opcl
{
	t_v3	oc;
	t_v3	r_p;
	t_v3	oc_p;
	float	pt;
}	t_opcl;

t_cl	*init_cl(char **arg);
int	add_light_cl(t_cl *cl, t_sc *sc, t_hit *hit);

#endif
