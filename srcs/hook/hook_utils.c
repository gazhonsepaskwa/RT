/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:55:30 by lderidde          #+#    #+#             */
/*   Updated: 2025/04/01 10:55:30 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Objects/transfo.h"
#include "../../includes/mlx_addon.h"
#include "../../includes/Minirt.h"
#include "../../includes/hook.h"
#include <stdlib.h>

void	free_sp(t_sc *sc, int i)
{
	if (sc->elems[i].sh.sp->tex.existb)
		free(sc->elems[i].sh.sp->tex.b.self);
	if (sc->elems[i].sh.sp->tex.existn)
		free(sc->elems[i].sh.sp->tex.n.self);
	free(sc->elems[i].sh.sp);
}

void	free_sc(t_sc *sc)
{
	int	i;

	i = -1;
	free_lights(sc);
	free(sc->cam);
	while (++i < sc->nb_objs)
	{
		if (sc->elems[i].type == SPHERE)
			free_sp(sc, i);
		else if (sc->elems[i].type == PLANE)
		{
			if (sc->elems[i].sh.pl->tex.existb)
				free(sc->elems[i].sh.pl->tex.b.self);
			if (sc->elems[i].sh.pl->tex.existn)
				free(sc->elems[i].sh.pl->tex.n.self);
			free(sc->elems[i].sh.pl);
		}
		else if (sc->elems[i].type == CYLINDER)
			free(sc->elems[i].sh.cl);
		else if (sc->elems[i].type == CONE)
			free(sc->elems[i].sh.cn);
	}
	free(sc->elems);
	free(sc);
}

int	close_win(t_mrt *mrt)
{
	mlx_destroy_image(mrt->g.xsrv, mrt->g.img[0].self);
	mlx_destroy_image(mrt->g.xsrv, mrt->g.img[1].self);
	mlx_destroy_window(mrt->g.xsrv, mrt->g.win);
	mlx_destroy_display(mrt->g.xsrv);
	free(mrt->g.xsrv);
	free_sc(mrt->sc);
	exit(EXIT_SUCCESS);
}
