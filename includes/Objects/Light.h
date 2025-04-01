/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:59:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/18 13:59:25 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "../Color.h"
# include "../Vec.h"

typedef struct s_sc	t_sc;

typedef struct s_li
{
	t_v3	pos;
	float	li;
	float	r;
	t_co	col;
}	t_li;

float	clump(float val, float min, float max);
t_li	*init_light(char **split);
t_li	*getlight(t_sc *sc);
t_co	init_color(char **arg);
int		col_to_int(t_co col);
void	free_lights(t_sc *sc);

#endif
