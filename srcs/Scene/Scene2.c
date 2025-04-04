/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:35:03 by nalebrun          #+#    #+#             */
/*   Updated: 2025/04/01 12:35:03 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../includes/Scene.h"
#include "../../includes/hook.h"

static t_co	init_acol(char *str)
{
	char	**split;
	t_co	co;

	split = ft_split(str, ",");
	if (!split)
		return ((t_co){0, 0, 0});
	co = init_color(split);
	free_tab(split);
	return (co);
}

static int	init_objp1(char **split, t_sc *sc, int i[2], void *xsrv)
{
	if (!ft_strncmp(split[0], "C", -1))
	{
		sc->cam = init_cam(split);
		if (!sc->cam)
			return (1);
	}
	else if (!ft_strncmp(split[0], "sp", -1))
	{
		sc->elems[i[0]].type = SPHERE;
		sc->elems[i[0]].sh.sp = init_sphere(split, xsrv);
		if (!sc->elems[i[0]++].sh.sp)
			return (1);
	}
	else if (!ft_strncmp(split[0], "L", -1))
	{
		sc->lig[i[1]] = init_light(split);
		if (!sc->lig[i[1]++])
			return (1);
	}
	return (0);
}

static int	init_objp2(char **split, t_sc *sc, int i[2], void *xsrv)
{
	if (!ft_strncmp(split[0], "pl", -1))
	{
		sc->elems[i[0]].type = PLANE;
		sc->elems[i[0]].sh.pl = init_plane(split, xsrv);
		if (!sc->elems[i[0]++].sh.pl)
			return (1);
	}
	else if (!ft_strncmp(split[0], "cl", -1))
	{
		sc->elems[i[0]].type = CYLINDER;
		sc->elems[i[0]].sh.cl = init_cl(split);
		if (!sc->elems[i[0]++].sh.cl)
			return (1);
	}
	else if (!ft_strncmp(split[0], "cn", -1))
	{
		sc->elems[i[0]].type = CONE;
		sc->elems[i[0]].sh.cn = init_cn(split);
		if (!sc->elems[i[0]++].sh.cn)
			return (1);
	}
	return (0);
}

static int	init_objp3(char **split, t_sc *sc)
{
	if (!ft_strncmp(split[0], "A", -1))
	{
		sc->li = ft_atof(split[1]);
		sc->col = init_acol(split[2]);
		return (0);
	}
	return (0);
}

int	init_objp0(char **split, t_sc *sc, int i[2], void *xsrv)
{
	if (init_objp1(split, sc, i, xsrv))
		return (free_sc(sc, xsrv, i[0] -2, sc->nb_lig -1), 1);
	if (init_objp2(split, sc, i, xsrv))
		return (free_sc(sc, xsrv, i[0] -2, sc->nb_lig -1), 1);
	if (init_objp3(split, sc))
		return (free_sc(sc, xsrv, i[0] -2, sc->nb_lig -1), 1);
	return (0);
}
