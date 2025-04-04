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
#include "../../../lib/libft/libft.h"
#include <stdlib.h>

t_li	*getlight(t_sc *sc)
{
	static int	i = 0;
	t_li		*ret;

	if (sc->lig[i])
	{
		ret = sc->lig[i];
		i = (i + 1) % sc->nb_lig;
		return (ret);
	}
	return ((void *)0);
}

int	col_to_int(t_co col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(col.r * 255);
	g = (int)(col.g * 255);
	b = (int)(col.b * 255);
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

void	free_lights(t_sc *sc, int li_lim)
{
	int	i;

	i = -1;
	while (++i <= li_lim)
		ft_free_v((void **)&sc->lig[i]);
	free(sc->lig);
}
