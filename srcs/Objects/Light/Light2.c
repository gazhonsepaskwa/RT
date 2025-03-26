/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:04 by lderidde          #+#    #+#             */
/*   Updated: 2025/03/26 11:31:04 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Objects/Light.h"
#include "../../../includes/Scene.h"

t_li	*getlight(t_sc *sc)
{
	int		i;

	i = -1;
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == LIGHT)
			return (sc->elems[i].sh.li);
	}
	return ((void *)0);
}

int	col_to_int(t_co col)
{
	int	r;
	int	g;
	int	b;

	r = (int)col.r * 255;
	g = (int)col.g * 255;
	b = (int)col.b * 255;
	return (r << 16 | g << 8 | b);
}

float	clump(float val, float min, float max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	else
		return (val);
}
