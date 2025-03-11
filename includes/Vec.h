/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:07:53 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/11 09:07:53 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <math.h>
# include <stdlib.h>

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
	int		px;
	int		py;
}	t_v3;

t_v3	cross(t_v3 a, t_v3 b);
t_v3	norm(t_v3 vec);
t_v3	vec_add(t_v3 v1, t_v3 v2);
t_v3	vec_scale(t_v3 vec, float scale);

#endif
