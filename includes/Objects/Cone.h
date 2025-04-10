/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:01:43 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/24 11:01:43 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "../Material.h"
# include "../Color.h"
# include "../Vec.h"
# include "Cylinder.h"

typedef struct s_cn
{
	t_v3	pos;
	t_v3	norm;
	t_v3	fw;
	t_v3	ri;
	t_mat	ma;
	t_co	col;
}	t_cn;

t_hit	draw_cn(t_hit tmp, t_cn *cn, t_v3 cam_pos);
t_cn	*init_cn(char **arg);
int		add_light_cn(t_cn *cn, t_sc *sc, t_hit *hit);
void	eval_color_cone(t_hit *hit, t_sc *sc, t_cn *cn);
t_mat	init_macn(char **arg);

#endif
